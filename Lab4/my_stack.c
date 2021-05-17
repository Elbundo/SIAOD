#include "my_stack.h"
#include <stdlib.h>

int stack_is_empty(stack *root)
{
	return !root?1:0;
}

void stack_push(stack **root, char* data)
{
	stack *tmp = malloc(sizeof(stack));
	tmp->data = data;
	tmp->next = *root;
	*root = tmp;
}

char* stack_pop(stack **root)
{
	if(*root == NULL)
		return NULL;
	stack *tmp = *root;
	*root = (*root)->next;
	char *data = tmp->data;
	free(tmp);
	return data;
}

void stack_clear(stack **root)
{
	while(*root){
		stack* tmp = *root;
		*root = (*root)->next;
		free(tmp);
	}
}
