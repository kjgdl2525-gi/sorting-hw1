#include "sort.h"
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int cmp(const void *a, const void *b) {
    int x = ((const Record *)a)->key, y = ((const Record *)b)->key;
    return (x > y) - (x < y);
}
static void check(const int *keys, size_t n, int alg) {
    Record a[256], ref[256];
    unsigned char seen[256] = {0};
    for (size_t i = 0; i < n; ++i) a[i] = ref[i] = (Record){keys[i], i};
    qsort(ref, n, sizeof(*ref), cmp);
    SortStats s = {0};
    assert(algorithms[alg].sort(a, n, &s));
    for (size_t i = 0; i < n; ++i) {
        assert(a[i].key == ref[i].key);
        assert(a[i].original < n && !seen[a[i].original]);
        assert(keys[a[i].original] == a[i].key);
        seen[a[i].original] = 1;
        if (algorithms[alg].stable && i && a[i-1].key == a[i].key)
            assert(a[i-1].original < a[i].original);
    }
}
int main(void) {
    const int examples[][8] = {{3,1,4,1,5,9,2,6},{1,2,3,4,5,6,7,8},
        {8,7,6,5,4,3,2,1},{2,2,2,2,2,2,2,2},{INT_MIN,0,INT_MAX,-1,1,0,INT_MIN,INT_MAX}};
    size_t checks = 0;
    uint32_t state = 42;
    for (int alg = 0; alg < 3; ++alg) {
        assert(algorithms[alg].sort(NULL, 0, NULL)); ++checks;
        for (size_t i = 0; i < 5; ++i) { check(examples[i], 8, alg); ++checks; }
        for (size_t n = 0; n <= 200; ++n) {
            int keys[256];
            for (size_t i = 0; i < n; ++i) {
                state = state * UINT32_C(1664525) + UINT32_C(1013904223);
                keys[i] = (int)(state % 31) - 15;
            }
            check(keys, n, alg); ++checks;
        }
    }
    Record a[] = {{1,0},{2,1},{3,2},{4,3}};
    SortStats s = {0};
    assert(insertionSort(a, 4, &s));
    assert(s.comparisons == 3 && s.moves == 6); ++checks;
    Record b[] = {{4,0},{3,1},{2,2},{1,3}};
    s = (SortStats){0};
    assert(insertionSort(b, 4, &s));
    assert(s.comparisons == 6 && s.moves == 12); ++checks;
    Record equal[] = {{2,0},{2,1},{2,2},{2,3}};
    assert(heapSort(equal, 4, NULL));
    int violation = 0;
    for (size_t i = 1; i < 4; ++i) if (equal[i-1].original > equal[i].original) violation = 1;
    assert(violation); ++checks;
    printf("%zu checks, 0 failures\n", checks);
    return 0;
}
