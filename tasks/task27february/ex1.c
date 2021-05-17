#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char stack[1000] = {0};
static int top = 0;

int main()
{
	void push(char);
	char pop();
	int isEmpty();
	int k = 0;
	char line[1000];
	if(scanf("%d", &k) != 1){
		printf("Error input!\n");
		exit(1);
	}
	if(k <= 0 || k > 1000){
		printf("Error intput!\n");
		exit(1);
	}
	for(int i = 0; i < k; i++){
		char c;
		int j = 0;
		getchar();
		while((c = getchar()) != ' ')
			line[j++] = c;
		line[j] = '\0';
		if(strcmp(line, "Vote") == 0){
			if(isEmpty() || pop() != getchar()){
				printf("No\n");
				exit(0);
			}
		}else if(strcmp(line, "Add") == 0){
			push(c=getchar());
		}else{
			printf("Error input!\n");
			exit(1);
		}
	}
	if(isEmpty()){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
	return 0;
}

void push(char c)
{
	stack[top++] = c;
}

char pop()
{
	return stack[--top];
}

int isEmpty()
{
	return !top;
}
