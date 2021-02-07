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
			swap(arr, i, min_i);
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
				swap(arr, j, j + 1);
		}
	}
}

void shell_sort(int* arr, const int n){
	for(int s = n / 2; s > 0; s /= 2){
		for(int i = 0; i < n; i++){
			for(int j = i + s; j < n; j += s){
				if(arr[i] > arr[j])
					swap(arr, i, j);
			}		
		}	
	}
}

void quick_sort(int* arr, int first, int last)
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
				swap(arr, left, right);
				left++;
				right--;
			}
		} while(left <= right);
		quick_sort(arr, first, right);
		quick_sort(arr, left, last);
	}			
}

void swap(int* arr, int a, int b)
{
	int tmp = arr[a];
	arr[a] = arr[b];
	arr[b] = tmp;
}
