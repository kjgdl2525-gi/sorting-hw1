#include "sort.h"
/* Iterative sink: avoids a recursive heapify stack. */
static void siftDown(Record *a, size_t root, size_t n, SortStats *s) {
    while (root < n / 2) {
        size_t child = 2 * root + 1;
        if (child + 1 < n && compareKeys(a[child].key, a[child + 1].key, s) < 0)
            ++child;
        if (compareKeys(a[root].key, a[child].key, s) >= 0) break;
        swapRecords(&a[root], &a[child], s);
        root = child;
    }
}
int heapSort(Record *a, size_t n, SortStats *s) {
    if (s) s->extra_bytes = n > 1 ? sizeof(Record) : 0;
    for (size_t i = n / 2; i > 0; --i) siftDown(a, i - 1, n, s);
    for (size_t end = n; end > 1; --end) {
        swapRecords(&a[0], &a[end - 1], s);
        siftDown(a, 0, end - 1, s);
    }
    return 1;
}
