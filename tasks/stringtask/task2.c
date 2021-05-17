#include <stdio.h>
#include <string.h>

char* getMaxPal(char*, int*);
int isPal(char*, int);

int main(int argc, char *argv[])
{
	int len;
	char* pal = getMaxPal(argv[1], &len);
	if(pal != NULL){
		pal[len] = '\0';
		printf("%s\n", pal);
	}else{
		printf("The string has not a pallinrome!\n");
	}
	return 0;
}

char* getMaxPal(char* str, int *length)
{
	for(*length = strlen(str); *length > 1; (*length)--){
		for(int j = 0; j < *length + 1; j++)
		{
			if(isPal(str+j, *length))
				return str+j;
		}
	}
	return NULL;
}

int isPal(char* str, int len)
{
	for(int i = 0; i < len/2; i++)
		if(*(str+i) != *(str+len-i-1))
			return 0;
	return 1;
}
