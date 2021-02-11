#ifndef MYSORT_H_SENTRY
#define MYSORT_H_SENTRY

#include <stdlib.h>

void selection_sort(int*, int);
void insertion_sort(int*, int);
void bubble_sort(int*, int);
void shell_sort(int*, int);
void my_qsort(int*, int);
void my_qsort_rec(int*, int, int);
void inc_qsort(int*, int);
void heap_sort(int*, int);
void build_heap(int*, int);
void sift_down(int*, int, int);
void swap(int*, int*);
int comp(const int*, const int*);
#endif
