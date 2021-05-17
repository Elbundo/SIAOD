#include <stdio.h>

int compare_num(int, int);
void sort(int*, int);
void swap(int*, int*);

int main()
{
	int N = 0;
	int k = scanf("%d", &N);
	if(k != 1)
		return 1;
	int arr[N];
	for(int i = 0; i < N; i++)
		if(scanf("%d", &arr[i]) != 1)
			return 1;	
	sort(arr, N);
	for(int i = 0; i < N; i++)
		printf("%d", arr[i]);
	printf("\n");
	return 1;
}


int compare_num(int x, int y)
{
	int k1 = 1, k2 = 1, a = x, b = y;
	while(a != 0 || b != 0){
		if(a > 0){
			a /= 10;
			k1 *= 10;
		}
		if(b > 0){
			b /= 10;
			k2 *= 10;
		}
	}
	if(x * k2 + y >= y * k1 + x)
		return 1; 
	return 0;
}

void sort(int* arr, int N)
{
	for(int i = 0; i < N - 1; i++){
		for(int j = i + 1; j < N; j++){
			if(i != j){
				if(!compare_num(arr[i], arr[j])){
					swap(&arr[i], &arr[j]);
				}
			}
		}
	}
}

void swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
