#include <stdio.h>
#include <string.h>

int getMaxPal(char* w);
int isCon(char*, int);

int main(int argc, char *argv[])
{
	int k = getMaxPal(argv[1]);
	printf("Number string: %d\n", k);
	return 0;
}

int getMaxPal(char* str)
{
	int count = 0;
	for(int length = strlen(str); length > 1; length--){
		for(int j = 0; j < length + 1; j++)
		{
			if(length % 2 == 0 && isCon(str+j, length))
				count++;
		}
	}
	return count;
}

int isCon(char* str, int len)
{
	for(int i = 0; i < len/2; i++)
		if(*(str+i) != *(str+len/2 + i))
			return 0;
	return 1;
}
