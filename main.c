#define _POSIX_C_SOURCE 200809L
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
static uint32_t nextRandom(uint32_t *state) {
    *state = *state * UINT32_C(1664525) + UINT32_C(1013904223);
    return *state;
}
static double now(void) {
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) { perror("clock_gettime"); exit(1); }
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}
static int keyOrder(const void *a, const void *b) {
    int x = ((const Record *)a)->key, y = ((const Record *)b)->key;
    return (x > y) - (x < y);
}
static int validate(const Record *a, const Record *ref, const Record *input, size_t n) {
    unsigned char *seen = calloc(n ? n : 1, 1);
    if (!seen) return 0;
    int ok = 1;
    for (size_t i = 0; i < n; ++i) {
        size_t tag = a[i].original;
        if (a[i].key != ref[i].key || tag >= n || seen[tag] || input[tag].key != a[i].key) {
            ok = 0; break;
        }
        seen[tag] = 1;
    }
    free(seen);
    return ok;
}
int main(void) {
    const size_t sizes[] = {1000, 2000, 4000, 8000, 16000};
    const char *shapes[] = {"random", "sorted", "reverse", "duplicates"};
    const int repeats = 5;
    printf("shape,n,algorithm,mean_ms,min_ms,max_ms,comparisons,moves,extra_bytes,stable_observed\n");
    for (size_t ni = 0; ni < 5; ++ni) for (int shape = 0; shape < 4; ++shape) {
        size_t n = sizes[ni], bytes = n * sizeof(Record);
        Record *input = malloc(bytes), *work = malloc(bytes), *ref = malloc(bytes);
        if (!input || !work || !ref) { fprintf(stderr, "allocation failed\n"); return 1; }
        uint32_t seed = UINT32_C(20260930) + (uint32_t)n + (uint32_t)shape;
        for (size_t i = 0; i < n; ++i) {
            int key;
            if (shape == 1) key = (int)i;
            else if (shape == 2) key = (int)(n - i);
            else key = (int)(nextRandom(&seed) % (shape == 3 ? 10u : 1000000u));
            input[i] = (Record){key, i};
        }
        memcpy(ref, input, bytes);
        qsort(ref, n, sizeof(*ref), keyOrder);
        double sum[3] = {0}, low[3] = {1e100,1e100,1e100}, high[3] = {0};
        /* One warm-up per algorithm; copies and correctness checks are untimed. */
        for (int a = 0; a < 3; ++a) {
            memcpy(work, input, bytes);
            if (!algorithms[a].sort(work, n, NULL) || !validate(work, ref, input, n)) return 2;
        }
        for (int r = 0; r < repeats; ++r) for (int step = 0; step < 3; ++step) {
            int a = (r + step) % 3; /* Rotate execution order. */
            memcpy(work, input, bytes);
            double start = now();
            int ok = algorithms[a].sort(work, n, NULL);
            double ms = (now() - start) * 1000;
            if (!ok || !validate(work, ref, input, n)) return 2;
            sum[a] += ms;
            if (ms < low[a]) low[a] = ms;
            if (ms > high[a]) high[a] = ms;
        }
        for (int a = 0; a < 3; ++a) {
            SortStats s = {0};
            memcpy(work, input, bytes);
            if (!algorithms[a].sort(work, n, &s) || !validate(work, ref, input, n)) return 2;
            int stable = 1;
            for (size_t i = 1; i < n; ++i)
                if (work[i-1].key == work[i].key && work[i-1].original > work[i].original) stable = 0;
            printf("%s,%zu,%s,%.6f,%.6f,%.6f,%llu,%llu,%zu,%d\n", shapes[shape], n,
                   algorithms[a].name, sum[a]/repeats, low[a], high[a],
                   (unsigned long long)s.comparisons, (unsigned long long)s.moves, s.extra_bytes, stable);
        }
        free(input); free(work); free(ref);
    }
    return 0;
}
