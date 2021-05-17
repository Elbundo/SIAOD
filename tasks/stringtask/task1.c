#include <stdio.h>

int main()
{
	char *s1 = "abe", *s2 = "acd";
	int k;
	for(; *s1 != '\0'; s1++){
		k = 0;
		for(int i = 0; s2[i] != '\0'; i++){
			if(*s1 <= s2[i])
				k++;
		}
		if(!k){
			printf("s1 can't win\n");
			return 0;
		}
	}
	printf("s1 can win\n");
	return 0;
}
