#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "my_strsrch.h"

int scan_str(char*);

int main()
{
	my_str* pattern;
	pattern = (my_str*)malloc(sizeof(my_str));
	//input_str(pattern);
	char* str = NULL;
	int n = scan_str(str);
	//printf("%s\n", pattern->buf);
	//printf("%s\n", str);
	for(int i = 0; i < 4; i++){
		//printf("%d ", str[i]);
	}
	printf("\n%d\n", n);
	printf("%ld\n", sizeof(str));
	free(pattern->buf);
	free(pattern);
	free(str);
	return 0;
}



