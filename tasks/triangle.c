#include <stdio.h>


int check_triangle(int a, int b, int c);

int main()
{
	int len = 0;
	int k = scanf("%d", &len);
	if(k != 1)
		return 1;
	int mass[len];
	for(int i = 0; i < len; i++){
		k = scanf("%d", &mass[i]);
		if(k != 1)
			return 1;
	}
	int max = 0;
	for(int i = 0; i < len - 2; i++){
		for(int j = i + 1; j < len - 1; j++){
			for(int k = j + 1; k < len; k++){
				int p = check_triangle(mass[i], mass[j], mass[k]);
				if(p > max)
					max = p;
			}
		}
	}
	printf("Max perimeter: %d\n", max);
	return 0;
}	

int check_triangle(int a, int b, int c)
{
	if((a + b > c) && (a + c > b) && (b + c > a))
		return a+b+c;
	return 0;
}
