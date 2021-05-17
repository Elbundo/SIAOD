#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ARR_ROW 3
#define ARR_COLUMN 3
#define MAX_VALUE 100

void sort(int (*)[ARR_COLUMN]);
void sort_diagonal(int (*)[ARR_COLUMN], int, int);
void swap(int*, int*);

int main()
{
	srand(time(NULL));
	int arr[ARR_ROW][ARR_COLUMN] = {0};
	for(int i = 0; i < ARR_ROW; i++){
		for(int j = 0; j < ARR_COLUMN; j++){
			arr[i][j] = rand() % MAX_VALUE;
			printf("%2.2d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	sort(arr);
	for(int i = 0; i < ARR_ROW; i++){
		for(int j = 0; j < ARR_COLUMN; j++){
			printf("%2.2d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void sort(int (*arr)[ARR_COLUMN])
{
	sort_diagonal(arr, 0, 0);
	for(int i = 1; i < ARR_ROW; i++)
		sort_diagonal(arr, i, 0);
	for(int i = 1; i < ARR_COLUMN; i++)
		sort_diagonal(arr, 0, i);	
}

void sort_diagonal(int (*arr)[ARR_COLUMN], int x, int y)
{
	while(x < ARR_ROW - 1  && y < ARR_COLUMN - 1){
		int i = x + 1, j = y + 1;
		while(i < ARR_ROW && j < ARR_COLUMN){
			if(arr[x][y] > arr[i][j])
				swap(&arr[x][y], &arr[i][j]);
			i++;
			j++;
		}
		x++;
		y++;
	}
}

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
