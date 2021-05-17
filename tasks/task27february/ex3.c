#include <stdio.h>

int main(int argc, char *argv[])
{
	char c;
	int k = 0, sum = 0;
	char *line = argv[1];
	for(int i = 0; line[i] != '\0'; i++){
		c = line[i];
		sum += c - '0';
		k++;
	}
	printf("k = %d\n", k);
	if(k == 1){
		printf("k == 1\n");
		if(c == '1' || c == '2' || c == '3' || c == '5' || c == '7'){
				printf("-1\n");
		}else if((c - '0') % 2 == 0){
				printf("10 2\n");
		}else if(c == '9'){
				printf("10 3\n");
		}
		return 0;
	}
	printf("%d %d\n", sum+1, sum);
	return 0;
}
