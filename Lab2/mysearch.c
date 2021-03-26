#include "mysearch.h"


int my_bsearch(int* arr, int n, int key)
{
	int begin = 0, end = n - 1, medium;
	while(begin <= end){
		medium = (begin + end) / 2;
		if(arr[medium] == key)
			return medium;
		if(arr[medium] > key)
			end = medium - 1;
		else
			begin = medium + 1;	
	}
	return -1;
}

int my_b(int* arr, int n, int key)
{
	int begin = 0, end = n - 1, medium;
	while(begin <= end){
		medium = (begin + end) / 2;
		if(arr[medium] == key)
			return medium;
		if(arr[medium] > key)
			end = medium - 1;
		else
			begin = medium + 1;	
	}
	return begin;
}

int my_intersearch(int *arr, int n, int key)
{
	int begin = 0, end = n - 1, prediction;
	while(arr[begin] < key && arr[end] > key){
		if(arr[begin] == arr[end])
			break;
		prediction = interfunc(begin, arr[begin], end, arr[end], key);
		if(arr[prediction] == key)
			return prediction;
		if(arr[prediction] > key)
			end = prediction - 1;
		else
			begin = prediction + 1;
	}
	if(arr[begin] == key)
		return begin;
	if(arr[end] == key)
		return end;
	return -1;
}


int my_i(int *arr, int n, int key)
{
	int begin = 0, end = n - 1, prediction;
	while(arr[begin] < key && arr[end] > key){
		if(arr[begin] == arr[end])
			break;
		prediction = interfunc(begin, arr[begin], end, arr[end], key);
		if(arr[prediction] == key)
			return prediction;
		if(arr[prediction] > key)
			end = prediction - 1;
		else
			begin = prediction + 1;
	}
	if(arr[begin] == key)
		return begin;
	if(arr[end] == key)
		return end;
	if(arr[end] < key)
		return ++end;
	return begin;
		
}

int interfunc(int x1, int y1, int x2, int y2, int key)
{
	return (((x2-x1)*(key-y1))/(y2-y1)) + x1;
}
