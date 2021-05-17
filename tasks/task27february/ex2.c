#include <stdio.h>
#include <math.h>

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 3; i < (int)sqrt(n) + 1; i++)
		if(n % i == 0){
			printf("%d\n", i);
			return 0;
		}
	if(n > 4 && n % 2 == 0){
		printf("%d\n", n / 2);
		return 0;
	}
	printf("%d\n", n);
	return 0;
}
