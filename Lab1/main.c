#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mysort.h"

#define ARR_LEN 1000

void cp_arr(int[ARR_LEN][ARR_LEN], int[ARR_LEN][ARR_LEN], int, int);
int comp(const int *, const int *);

int main(int argc, char* argv[])
{
	clock_t begin, end;
	double time_select, time_insert, time_bubble, time_shell, time_my_quick, time_quick;
	srandom(time(NULL));
	int arr[ARR_LEN][ARR_LEN], sort_arr[ARR_LEN][ARR_LEN];
	for(int i = 0; i < ARR_LEN; i++){
		for(int j = 0; j < ARR_LEN; j++){
			arr[i][j] = random() % ARR_LEN;
		}
	}
	cp_arr(arr, sort_arr, ARR_LEN, ARR_LEN);
	begin = clock();
	for(int i = 0; i < ARR_LEN; i++){
		selection_sort(sort_arr[i], ARR_LEN);
	}
	end = clock();
	time_select = (double)(end - begin) / CLOCKS_PER_SEC;
	
	cp_arr(arr, sort_arr, ARR_LEN, ARR_LEN);
	begin = clock();
	for(int i = 0; i < ARR_LEN; i++){
		insertion_sort(sort_arr[i], ARR_LEN);
	}
	end = clock();
	time_insert = (double)(end - begin) / CLOCKS_PER_SEC;
	
	cp_arr(arr, sort_arr, ARR_LEN, ARR_LEN);
	begin = clock();
	for(int i = 0; i < ARR_LEN; i++){
		bubble_sort(sort_arr[i], ARR_LEN);
	}
	end = clock();
	time_bubble = (double)(end - begin) / CLOCKS_PER_SEC;
	
	cp_arr(arr, sort_arr, ARR_LEN, ARR_LEN);
	begin = clock();
	for(int i = 0; i < ARR_LEN; i++){
		shell_sort(sort_arr[i], ARR_LEN);
	}
	end = clock();
	time_shell = (double)(end - begin) / CLOCKS_PER_SEC;
	
	cp_arr(arr, sort_arr, ARR_LEN, ARR_LEN);
	begin = clock();
	for(int i = 0; i < ARR_LEN; i++){
		quick_sort(sort_arr[i], 0, ARR_LEN);
	}
	end = clock();
	time_my_quick = (double)(end - begin) / CLOCKS_PER_SEC;
	
	cp_arr(arr, sort_arr, ARR_LEN, ARR_LEN);
	begin = clock();
	for(int i = 0; i < ARR_LEN; i++){
		qsort(sort_arr[i], ARR_LEN, sizeof(int), (int(*)(const void *, const void *))comp);
	}
	end = clock();
	time_quick = (double)(end - begin) / CLOCKS_PER_SEC;
	
	printf("\n");
	
	printf("Selection sort run time - %.2f s \n", time_select);
	printf("Insertion sort run time - %.2f s \n", time_insert);
	printf("Bubble sort run time    - %.2f s \n", time_bubble);
	printf("Shell sort run time     - %.2f s \n", time_shell);
	printf("My quick sort run time  - %.2f s \n", time_my_quick);
	printf("Quick sort run time     - %.2f s \n", time_quick);
	return 0;
}

void cp_arr(int from[ARR_LEN][ARR_LEN], int to[ARR_LEN][ARR_LEN], int columns, int rows){
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){
			to[i][j] = from[i][j];
		}
	}
}

int comp(const int* a, const int* b)
{
	return *a - *b;
}
