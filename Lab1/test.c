#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_LEN 10

void cup_sort(int*, int);


int main()
{
	srand(time(NULL));
	int arr[ARR_LEN];
	for(int i = 0; i < ARR_LEN; i++){
		arr[i] = rand() % ARR_LEN;
	}




	for(int i = 0; i < ARR_LEN; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
	return 0;
}
