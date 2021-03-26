#include "my_strsrch.h"
#include <stdlib.h>
#include <stdio.h>

void input_str(my_str* str)
{
	if(str != NULL)
		str->length = scan_str(str->buf);
}


int scan_str(char* str){
	int c  = 0, n = 1, count = 0;
	char *buf = NULL;
	if(str != NULL)
		free(str);
	str = (char*)malloc(n);
	while((c = getchar()) != '\n'){
		count++;
		if(count >= n){
			n *= 2;
			buf = str;
			str = (char*)malloc(n);
			for(int i = 0; i < count; i++){
				str[i] = buf[i];
			}
			free(buf);
		}
		str[count] = (char)c;
	}
	if(count != n-1){
		buf = str;
		str = (char*)malloc(count+1);
		for(int i = 0; i < count; i++){
			str[i] = buf[i];
		}
	}
	str[count] = '\0';
	free(buf);
	return count;
}
