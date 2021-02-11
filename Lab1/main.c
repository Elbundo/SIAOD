#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mysort.h"

#define ARR_LEN 1000
#define f_count 7

void cp_arr(int[ARR_LEN][ARR_LEN], int[ARR_LEN][ARR_LEN], int, int);

typedef struct sort_func
{
	char* name;
	void (*func)(int*, int);
} sort_f; 

int main(int argc, char* argv[])
{
	srandom(time(NULL));
	clock_t begin, end;
	int arr[ARR_LEN][ARR_LEN], sort_arr[ARR_LEN][ARR_LEN];
	sort_f sort_functions[] = {
		{"Selection sort", &selection_sort},
		{"Insertion sort", &insertion_sort},
		{"Bubble sort", &bubble_sort},
		{"Shell sort", &shell_sort},
		{"My quick sort", &my_qsort},
		{"Quick sort", &inc_qsort},
		{"Heap sort", &heap_sort}
	};
	for(int i = 0; i < ARR_LEN; i++){
		for(int j = 0; j < ARR_LEN; j++){
			arr[i][j] = random() % ARR_LEN;
		}
	}
	for(int i = 0; i < f_count; i++){
		cp_arr(arr, sort_arr, ARR_LEN, ARR_LEN);
		begin = clock();
		for(int j = 0; j < ARR_LEN; j++){
			(*(sort_functions[i].func))(sort_arr[j], ARR_LEN);
		}
		end = clock();
		printf("%s run time - %.2f s \n", sort_functions[i].name, (double)(end - begin) / CLOCKS_PER_SEC);
	}

	return 0;
}

void cp_arr(int from[ARR_LEN][ARR_LEN], int to[ARR_LEN][ARR_LEN], int columns, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			to[i][j] = from[i][j];
		}
	}
}


