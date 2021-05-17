#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include "my_stack.h"
#include "my_deque.h"

#define MAXLINE 1000

void task1();
void task2();
void task3();
void task4();
void task5();
void task6();
void task7();
void task8();
void task9();
void task10();
void task11();

void write_solutions();
void my_cat(char, int);
char* join_path(char*, char, int);

void swap_tower(stack**, stack**, stack**, int);
int comp(const char*, const char*);
char decrypt(deque*, char);
int priority(char);

int main()
{
	task1();
	task2();
	task3();
	task4();
	task5();
	task6();
	task7();
	task8();
	task9();
	task10();
	task11();

	write_solutions();
	return 0;
}

void write_solutions()
{
	for(int i = 1; i <= 11; i++){
		printf("------------Task %d--------------\n", i);
		printf("Input file:\n");
		my_cat('i', i);
		printf("Output file:\n");
		my_cat('o', i);
		printf("---------------------------------\n\n");
	}
}

void my_cat(char mode, int i)
{
	char path[100];
	int pid;
	pid = fork();
	if(pid == -1){
		perror("fork");
		exit(1);
	}
	if(pid == 0){
		execlp("cat", "cat", join_path(path, mode, i), NULL);
		perror("cat");
		exit(1);
	}
	wait(NULL);
}

char* join_path(char* path, char m, int n)
{
	char *str = "_task", *end = ".txt";
	int i = 0;
	path[i++] = m;
	memcpy(path+i, str, strlen(str));
	i += strlen(str);
	if(n < 10){
		path[i++] = n + '0';
	}else{
		path[i++] = (n/10) + '0';
		path[i++] = (n%10) + '0';
	}
	memcpy(path+i, end, strlen(end));
	i += strlen(end);
	path[i] = '\0';
	return path;
}

void task1()
{
	deque *main = create_deque();
	deque *minor = create_deque();
	char *ptr = NULL;
	int length = 0;
	size_t size = MAXLINE;
	FILE* f1 = fopen("i_task1.txt", "r");
	while((length = getline(&ptr, &size, f1)) > 0){
		char *line = malloc((length+1)*sizeof(char));
		memcpy(line, ptr, length+1);
		if(deque_is_empty(main)){
			deque_push_back(main, line);
		}else{
			char *tmp = NULL;
			while(!deque_is_empty(main) && comp((tmp = deque_pop_back(main)), line) < 0){
				deque_push_front(minor, tmp);
			}
			if(!deque_is_empty(main))
				deque_push_back(main, tmp);
			deque_push_back(main, line);
			while(!deque_is_empty(minor))
				deque_push_back(main, deque_pop_front(minor));
		}
	}
	FILE* out = fopen("o_task1.txt", "wt");
	while(!deque_is_empty(main))
		fprintf(out, "%s", deque_pop_back(main));
	fclose(out);
	fclose(f1);
}

int comp(const char *s1, const char *s2)
{
	int i;
	for(i = 0; s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]; i++)
		;
	if((s1[i] == '\0' && s2[i] == '\0')){
		return 0;
	}else if(s1[i] == '\0' || (s1[i] < s2[i])){
		return -1;
	}else if(s2[i] == '\0' || (s2[i] < s1[i])){
		return 1;
	}
	return 0;
}

void task2()
{
	deque *deq = create_deque();
	FILE* f2 = fopen("i_task2.txt", "r");
	FILE* out = fopen("o_task2.txt", "wt");
	int c = 0;
	for(c = 0; c < 256; c++){
		char *ptr = malloc(sizeof(char));
		*ptr = (char)c;
		deque_push_back(deq, ptr);
	}
	while((c = fgetc(f2)) != EOF && c != '\n'){
		fputc(decrypt(deq, (char)c), out);
	}
	fputc('\n', out);
	fclose(out);
	fclose(f2);
}

char decrypt(deque* deq, char c)
{
	char* r;
	do{
		r = deque_pop_front(deq);
		deque_push_back(deq, r);
	}while(*r != c);
	deque_push_back(deq, deque_pop_front(deq));
	r = deque_pop_front(deq);
	deque_push_back(deq, r);
	return *r;
}

void task3()
{
	stack *A = NULL, *B = NULL, *C = NULL;
	FILE* f3 = fopen("i_task3.txt", "r");
	int a, b;
	int count = 0;
	while((b = fscanf(f3, "%d", &a)) != -1){
		char* ptr = malloc(sizeof(char));
		*ptr = (char)a;
		stack_push(&A, ptr);
		count++;
	}
	swap_tower(&A, &B, &C, count);
	FILE *out = fopen("o_task3.txt", "wt");
	fprintf(out, "A: ");
	while(!stack_is_empty(A)){
		char *ptr = stack_pop(&A);
		fprintf(out, "%d ", (int)*ptr);
		free(ptr);
	}
	fprintf(out, "\n");
	fprintf(out, "B: ");
	while(!stack_is_empty(B)){
		char *ptr = stack_pop(&B);
		fprintf(out, "%d ", (int)*ptr);
		free(ptr);
	}
	fprintf(out, "\n");
	fprintf(out, "C: ");
	while(!stack_is_empty(C)){
		char *ptr = stack_pop(&C);
		fprintf(out, "%d ", (int)*ptr);
		free(ptr);
	}
	fprintf(out, "\n");
	fclose(out);
	fclose(f3);
}

void swap_tower(stack **src, stack **dist, stack **buf, int n)
{
	if(n <= 0)
		return;
	swap_tower(src, buf, dist, n-1);
	stack_push(dist, stack_pop(src));
	swap_tower(buf, dist, src, n-1);
}

void task4()
{
	stack *root = NULL;
	FILE* f4 = fopen("i_task4.txt", "r");
	FILE* out = fopen("o_task4.txt", "wt");
	int c = 0;
	while((c = fgetc(f4)) != EOF){
		if(c == '{'){
			stack_push(&root, (char*)&c);
		}else if(c == '}'){
			if(stack_is_empty(root)){
				fprintf(out, "Breakets is not good!\n");
				return;
			}
			stack_pop(&root);
		}
	}
	if(stack_is_empty(root))
		fprintf(out, "Breakets is good!\n");
	else
		fprintf(out, "Breakets is not good\n");
	fclose(out);
	fclose(f4);
}

void task5()
{
	deque *deq = create_deque();
	FILE* f5 = fopen("i_task5.txt", "r");
	FILE* out = fopen("o_task5.txt", "wt");
	int c = 0;
	while((c = fgetc(f5)) != EOF){
		if(c == '['){
			deque_push_back(deq, (char*)&c);
		}else if(c == ']'){
			if(!(deq->head)){
				fprintf(out, "Breakets is not good!\n");
				return;
			}
			deque_pop_back(deq);
		}
	}
	if(deque_is_empty(deq))
		fprintf(out, "Breakets is good!\n");
	else
		fprintf(out, "Breakets is not good\n");
	fclose(out);
	fclose(f5);
}

void task6()
{
	deque *deq = create_deque();
	FILE* f6 = fopen("i_task6.txt", "r");
	FILE* out = fopen("o_task6.txt", "wt");
	int c = 0;
	while((c = fgetc(f6)) != EOF){
		if(isdigit(c)){
			fprintf(out, "%c", c);
		}else if(isalpha(c)){
			char* ptr = malloc(sizeof(char));
			*ptr = (char)c;
			deque_push_front(deq, ptr);
		}else{
			char* ptr = malloc(sizeof(char));
			*ptr = (char)c;
			deque_push_back(deq, ptr);	
		}
	}
	char* ptr;
	while(!isalpha(*(ptr = deque_pop_back(deq)))){

		deque_push_front(deq, ptr);
	}
	while(isalpha((c = *deque_pop_back(deq)))){
		fprintf(out, "%c", c);
	}
	while(!deque_is_empty(deq)){
		fprintf(out, "%c", *deque_pop_front(deq));
	}
	fprintf(out, "\n");
	fclose(out);
	fclose(f6);
}

void task7()
{
	deque *deq = create_deque();
	FILE* f7 = fopen("i_task7.txt", "r");
	int a, b;
	while((b = fscanf(f7, "%d", &a)) != -1){
		char* ptr = malloc(sizeof(char));
		*ptr = (char)a;
		if(a < 0){
			deque_push_front(deq, ptr);
		}else{
			deque_push_back(deq, ptr);
		}
	}
	char *ptr;
	while(*(ptr = deque_pop_front(deq)) < 0){
		deque_push_back(deq, ptr);
	}
	deque_push_front(deq, ptr);
	FILE* out = fopen("o_task7.txt", "wt");
	while(*(ptr = deque_pop_back(deq)) < 0){
		fprintf(out, "%d ", *ptr);
		free(ptr);
	}
	deque_push_back(deq, ptr);
	while(!deque_is_empty(deq)){
		ptr = deque_pop_front(deq);
		fprintf(out, "%d ", *ptr);
		free(ptr);
	}
	fprintf(out, "\n");
	free(deq);
	fclose(out);
	fclose(f7);
}

void task8()
{
	stack *root = NULL;
	FILE* f8 = fopen("i_task8.txt", "r");
	char *ptr = NULL;
	size_t size = MAXLINE;
	while(getline(&ptr, &size, f8) > 0){
		char *line = ptr;
		ptr = NULL;
		stack_push(&root, line);
	}
	FILE* out = fopen("o_task8.txt", "wt");
	while(!stack_is_empty(root)){
		char *ptr = stack_pop(&root);
		fprintf(out, "%s", ptr);
		free(ptr);
	}
	fclose(out);
	fclose(f8);
}

void task9()
{
	stack *root = NULL;
	stack *result = NULL;
	FILE* f9 = fopen("i_task9.txt", "r");
	int c, err = 0;
	while((c = fgetc(f9)) != EOF){
		if(c == ' ')
			continue;
		if(c == 'T' || c == 'F' || c == 't' || c == 'f'){
			char *ptr = malloc(sizeof(char));
			*ptr = c;
			stack_push(&result, ptr);
		}else if(c == '(' || c == 'N' || c == 'n'){
			char *ptr = malloc(sizeof(char));
			*ptr = c;
			stack_push(&root, ptr);
		}else if(c == ')'){
			char *ptr;
			while(!stack_is_empty(root) && *(ptr = stack_pop(&root)) != '('){
				stack_push(&result, ptr);
			}
			if(*ptr != '('){
				err = 1;
				break;
			}
		}else if(c == 'A' || c == 'a' || c == 'X' || c == 'x' || c == 'O' || c == 'o'){
			char *ptr;
			while(!stack_is_empty(root)){
				ptr = stack_pop(&root);
				if(priority(c) <= priority(*ptr)){
					stack_push(&result, ptr);
				}else{
					stack_push(&root, ptr);	
					break;
				}
			}
			ptr = malloc(sizeof(char));
			*ptr = c;
			stack_push(&root, ptr);
		}
	}
	if(c == 'A' || c == 'a' || c == 'X' || c == 'x' || c == 'O' || c == 'o')
		err = 1;
	while(!stack_is_empty(root)){
		char* ptr = stack_pop(&root);
		if(priority(*ptr) == 4 || priority(*ptr) == 0){
			err = 1;
			break;
		}
		stack_push(&result, ptr);
	}
	stack *buf = result;
	result = NULL;
	while(!stack_is_empty(buf)){
		stack_push(&result, stack_pop(&buf));
	}
	FILE* out = fopen("o_task9.txt", "wt");
	if(err){
		fprintf(out, "The expression is not valid!\n");
		fclose(out);
		return;
	}else{
		while(!stack_is_empty(result)){
			char *ptr = stack_pop(&result);
			if(*ptr == 'T' || *ptr == 't' || *ptr == 'F' || *ptr == 'f'){
				stack_push(&root, ptr);
			}else if(*ptr == 'N' || *ptr == 'n'){
				if(stack_is_empty(root)){
					err = 1;
					break;
				}
				char *cptr = stack_pop(&root);
				if(*cptr == 'T' || *cptr == 't'){
					*cptr = 'F';
				}else if(*cptr == 'F' || *cptr == 'f'){
					*cptr = 'T';
				}else{
					err = 1;
					break;
				}
				stack_push(&root, cptr);
			}else if(*ptr == 'A' || *ptr == 'a' || *ptr == 'O' || *ptr == 'o' || *ptr == 'X' || *ptr == 'x'){
				char *aptr = stack_pop(&root);
				char *bptr = stack_pop(&root);
				//if(*aptr != 'T' && *aptr != 't' && *aptr != 'F' && *aptr != 'f' && *bptr != 'T' && *bptr != 't' && *bptr != 'F' && *bptr != 'f'){
				//	err = 1;
				//	break;
				//}
				if(*ptr == 'A' || *ptr == 'a'){
					*ptr = ((*aptr == 'T' || *aptr == 't') && (*bptr == 'T' || *bptr == 't')) ? 'T' : 'F';
				}else if(*ptr == 'O' || *ptr == 'o'){
					*ptr = ((*aptr == 'T' || *aptr == 't') || (*bptr == 'T' || *bptr == 't')) ? 'T' : 'F';
				}else if(*ptr == 'X' || *ptr == 'x'){
					*ptr = ((!(*aptr == 'T' || *aptr == 't') && (*bptr == 'T' || *bptr == 't')) || ((*aptr == 'T' || *aptr == 't') && !(*bptr == 'T' || *bptr == 't'))) ? 'T' : 'F';
				}
				free(aptr);
				free(bptr);
				stack_push(&root, ptr);
			}
		}
	}
	if(stack_is_empty(root) || err){
		fprintf(out, "The expression is not valid!");
	}else{
		char *ptr = stack_pop(&root);
		fputc(*ptr, out);
		free(ptr);
	}
	fputc('\n', out);
	fclose(out);
	fclose(f9);
}

int priority(char c)
{
	switch(c){
		case 'o': case 'O': case 'X': case 'x': case '+': case '-':
			return 1;
		case 'A': case 'a':
			return 2;
		case 'N': case 'n':
			return 3;
		case '(': case ')':
			return 0;
	}
	return 0;
}


void task10()
{
	stack *root = NULL, *result = NULL;
	FILE* f10 = fopen("i_task10.txt", "r");
	int c, err = 0;
	while((c = fgetc(f10)) != EOF){
		if(c == ' ')
			continue;
		if(c == 'N' || c == 'M' || isdigit(c)){
			char *ptr = malloc(sizeof(char));
			*ptr = c;
			stack_push(&result, ptr);
		}
	}
	while(!stack_is_empty(result)){
		char *ptr = stack_pop(&result);
		if(isdigit(*ptr)){
			stack_push(&root, ptr);
		}else if(*ptr == 'M'){
			char *aptr, *bptr;
			if(stack_is_empty(root)){
				err = 1;
				break;
			}
			aptr = stack_pop(&root);
			if(stack_is_empty(root)){
				err = 1;
				break;
			}
			bptr = stack_pop(&root);
			if(!isdigit(*aptr) || !isdigit(*bptr)){
				err = 1;
				break;
			}
			*ptr = *aptr > *bptr ? *aptr : *bptr;
			stack_push(&root, ptr);
		}else if(*ptr == 'N'){
			char *aptr, *bptr;
			if(stack_is_empty(root)){
				err = 1;
				break;
			}
			aptr = stack_pop(&root);
			if(stack_is_empty(root)){
				err = 1;
				break;
			}
			bptr = stack_pop(&root);
			if(!isdigit(*aptr) || !isdigit(*bptr)){
				err = 1;
				break;
			}
			*ptr = *aptr < *bptr ? *aptr : *bptr;
			stack_push(&root, ptr);
			free(aptr);
			free(bptr);
		}
	}
	FILE* out = fopen("o_task10.txt", "wt");
	if(stack_is_empty(root) || err){
		fprintf(out, "The expression is not valid!\n");	
	}else{
		char *ptr = stack_pop(&root);
		fprintf(out, "%c\n", *ptr);
		free(ptr);
	}
	fclose(out);
	fclose(f10);
}

void task11()
{
	stack *root = NULL;
	stack *result = NULL;
	FILE* f11 = fopen("i_task11.txt", "r");
	int c, err = 0;
	while((c = fgetc(f11)) != EOF){
		if(c == ' ')
			continue;
		if(c == 'x' || c == 'y' || c == 'z'){
			char *ptr = malloc(sizeof(char));
			*ptr = c;
			stack_push(&result, ptr);
		}else if(c == '('){
			char *ptr = malloc(sizeof(char));
			*ptr = c;
			stack_push(&root, ptr);
		}else if(c == ')'){
			char *ptr;
			while(!stack_is_empty(root) && *(ptr = stack_pop(&root)) != '('){
				stack_push(&result, ptr);
			}
			if(*ptr != '('){
				err = 1;
				break;
			}
		}else if(c == '+' || c == '-'){
			char *ptr;
			while(!stack_is_empty(root)){
				ptr = stack_pop(&root);
				if(priority(c) <= priority(*ptr)){
					stack_push(&result, ptr);
				}else{
					stack_push(&root, ptr);	
					break;
				}
			}
			ptr = malloc(sizeof(char));
			*ptr = c;
			stack_push(&root, ptr);
		}
	}
	if(c == '+' || c == '-')
		err = 1;
	while(!stack_is_empty(root)){
		char* ptr = stack_pop(&root);
		if(priority(*ptr) == 4 || priority(*ptr) == 0){
			err = 1;
			break;
		}
		stack_push(&result, ptr);
	}
	stack *buf = result;
	result = NULL;
	while(!stack_is_empty(buf)){
		stack_push(&result, stack_pop(&buf));
	}
	FILE* out = fopen("o_task11.txt", "wt");
	if(err){
		fprintf(out, "The expression is not valid!\n");
	}else{
		while(!stack_is_empty(result)){
			char *ptr = stack_pop(&result);
			if(*ptr == 'x' || *ptr == 'y' || *ptr == 'z'){
				stack_push(&root, ptr);
			}else if(*ptr == '+' || *ptr == '-'){
				if(stack_is_empty(root)){
					err = 1;
					break;
				}
				char *aptr = stack_pop(&root);
				if(stack_is_empty(root)){
					err = 1;
					break;
				}
				char *bptr = stack_pop(&root);
				if(*aptr != 'x' && *aptr != 'y' && *aptr != 'z'){
					err = 1;
					break;
				}
				*ptr = 'x';
				free(aptr);
				free(bptr);
				stack_push(&root, ptr);
			}
		}
	}
	if(stack_is_empty(root) || err){
		fprintf(out, "The expression is not valid!\n");
	}else{
		fprintf(out, "The expression is valid!\n");
	}
	fclose(out);
	fclose(f11);
}

