#ifndef SORT_H
#define SORT_H
#include <stddef.h>
#include <stdint.h>
typedef struct { int key; size_t original; } Record;
typedef struct { uint64_t comparisons, moves; size_t extra_bytes; } SortStats;
typedef int (*SortFn)(Record *, size_t, SortStats *);
typedef struct { const char *name; SortFn sort; int stable; } Algorithm;
extern const Algorithm algorithms[3];
int insertionSort(Record *, size_t, SortStats *);
int mergeSort(Record *, size_t, SortStats *);
int heapSort(Record *, size_t, SortStats *);
int compareKeys(int, int, SortStats *);
void moveRecord(Record *, Record, SortStats *);
void swapRecords(Record *, Record *, SortStats *);
#endif
