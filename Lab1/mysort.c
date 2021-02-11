#include "mysort.h"


void selection_sort(int* arr, const int n)
{
	int min_i;
	for(int i = 0; i < n - 1; i++){
		min_i = i;
		for(int j = i + 1; j < n; j++){
			if(arr[j] < arr[min_i])
				min_i = j;
		}
		if(min_i != i)
			swap(&arr[i], &arr[min_i]);
	}
}

void insertion_sort(int* arr, const int n)
{
	int cur, j;
	for(int i = 1; i < n; i++){
		cur = arr[i];
		j = i - 1;
		while(j >= 0 && arr[j] > cur){
			arr[j + 1] = arr[j];
			j--;	
		}
		arr[j + 1] = cur;
	}
}

void bubble_sort(int* arr, const int n)
{
	for(int i = 0; i < n - 1; i++){
		for(int j = 0; j < n - 1 - i; j++){
			if(arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
		}
	}
}

void shell_sort(int* arr, const int n){
	for(int s = n / 2; s > 0; s /= 2){
		for(int i = 0; i < n; i++){
			for(int j = i + s; j < n; j += s){
				if(arr[i] > arr[j])
					swap(&arr[i], &arr[j]);
			}		
		}	
	}
}

void my_qsort(int* arr, int n)
{
	my_qsort_rec(arr, 0, n);
}

void my_qsort_rec(int* arr, int first, int last)
{
	if(first < last){
		int left = first, right = last, middle = arr[(left + right) / 2];
		do
		{
			while(arr[left] < middle)
				left++;
			while(arr[right] > middle)
				right--;
			if(left <= right){
				swap(&arr[left], &arr[right]);
				left++;
				right--;
			}
		} while(left <= right);
		my_qsort_rec(arr, first, right);
		my_qsort_rec(arr, left, last);
	}			
}

void inc_qsort(int* arr, int n)
{
	qsort(arr, n, sizeof(int), (int(*)(const void *, const void *))comp);
}

void heap_sort(int* arr, int n){
	build_heap(arr, n);
	while(n > 1){
		swap(&arr[0], &arr[n - 1]);
		n--;
		sift_down(arr, 0, n);
	}
}

void build_heap(int* arr, int n)
{
	for(int i = (n / 2) - 1; i >= 0; i--)
		sift_down(arr, i, n);
}

void sift_down(int* arr, int i, int n)
{
	int l = 2 * i + 1, r = 2 * i + 2, larg = i;
	if(l < n && arr[l] > arr[i])
		larg = l;
	if(r < n && arr[r] > arr[larg])
		larg = r;
	if(larg != i){
		swap(&arr[i], &arr[larg]);
		sift_down(arr, larg, n);
	}
}

void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int comp(const int* a, const int* b)
{
	return *a - *b;
}

