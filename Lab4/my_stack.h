#ifndef MY_STACK_H_SENTRY
#define MY_STACK_H_SENTRY

typedef struct my_stack{
	char *data;
	struct my_stack *next;
} stack;

int stack_is_empty(stack*);
void stack_push(stack**, char*);
char* stack_pop(stack**);
void stack_clear(stack**);

#endif
