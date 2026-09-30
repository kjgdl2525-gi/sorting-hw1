#include "sort.h"
#include <stdlib.h>
/* Standard top-down mergesort; no presorted-range shortcut. */
static void sortRange(Record *a, Record *tmp, size_t lo, size_t hi, SortStats *s) {
    if (hi - lo < 2) return;
    size_t mid = lo + (hi - lo) / 2;
    sortRange(a, tmp, lo, mid, s);
    sortRange(a, tmp, mid, hi, s);
    size_t i = lo, j = mid, k = lo;
    while (i < mid && j < hi) {
        /* Left-first on equality preserves stability. */
        if (compareKeys(a[i].key, a[j].key, s) <= 0)
            moveRecord(&tmp[k++], a[i++], s);
        else moveRecord(&tmp[k++], a[j++], s);
    }
    while (i < mid) moveRecord(&tmp[k++], a[i++], s);
    while (j < hi) moveRecord(&tmp[k++], a[j++], s);
    for (k = lo; k < hi; ++k) moveRecord(&a[k], tmp[k], s);
}
int mergeSort(Record *a, size_t n, SortStats *s) {
    if (n < 2) return 1;
    if (n > SIZE_MAX / sizeof(Record)) return 0;
    Record *tmp = malloc(n * sizeof(*tmp));
    if (!tmp) return 0;
    if (s) s->extra_bytes = n * sizeof(*tmp);
    sortRange(a, tmp, 0, n, s);
    free(tmp);
    return 1;
}
