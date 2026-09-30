#include "sort.h"
int insertionSort(Record *a, size_t n, SortStats *s) {
    if (s) s->extra_bytes = n > 1 ? sizeof(Record) : 0;
    for (size_t i = 1; i < n; ++i) {
        Record key;
        moveRecord(&key, a[i], s);
        size_t j = i;
        while (j > 0 && compareKeys(a[j - 1].key, key.key, s) > 0) {
            moveRecord(&a[j], a[j - 1], s);
            --j;
        }
        moveRecord(&a[j], key, s);
    }
    return 1;
}
