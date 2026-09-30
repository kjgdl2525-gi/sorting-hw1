#include "sort.h"
const Algorithm algorithms[3] = {
    {"insertion", insertionSort, 1}, {"merge", mergeSort, 1}, {"heap", heapSort, 0}
};
/* Count key comparisons only; index/loop tests are excluded. */
int compareKeys(int a, int b, SortStats *s) {
    if (s) ++s->comparisons;
    return (a > b) - (a < b);
}
/* One Record assignment is one move, including assignments to temporaries. */
void moveRecord(Record *to, Record from, SortStats *s) {
    *to = from;
    if (s) ++s->moves;
}
void swapRecords(Record *a, Record *b, SortStats *s) {
    Record tmp;
    moveRecord(&tmp, *a, s);
    moveRecord(a, *b, s);
    moveRecord(b, tmp, s);
}
