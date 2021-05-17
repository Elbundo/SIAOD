#include <stdlib.h>
#include "my_deque.h"

deque* create_deque()
{
	deque* root = malloc(sizeof(deque));
	root->head = NULL;
	root->tail = NULL;
	return root;
}

int deque_is_empty(deque *root)
{
	return !(root->head)?1:0;
}


void deque_push_back(deque *root, char* data)
{
	list* tmp = malloc(sizeof(list));
	tmp->data = data;
	tmp->next = NULL;
	if(!(root->tail)){
		tmp->prev = NULL;
		root->tail = tmp;
		root->head = tmp;

	}else{
		tmp->prev = root->tail;
		root->tail->next = tmp;
		root->tail = root->tail->next;
	}


}

void deque_push_front(deque *root, char* data)
{
	list* tmp = malloc(sizeof(list));
	tmp->data = data;
	tmp->next = root->head;
	tmp->prev = NULL;
	if(root->head != NULL)
		root->head->prev = tmp;
	root->head = tmp;
	if(root->tail == NULL)
		root->tail = tmp;
}

char* deque_pop_back(deque *root)
{
	char* data = NULL;
	list* tmp = root->tail;
	data = tmp->data;
	if(root->head == root->tail){
		root->head = NULL;
		root->tail = NULL;
	}else{
		root->tail = root->tail->prev;
		root->tail->next = NULL;	
	}
	free(tmp);
	return data;	
}

char* deque_pop_front(deque *root)
{
	char* data = NULL;
	list* tmp = root->head;
	root->head = root->head->next;
	data = tmp->data;
	free(tmp);
	if(root->head == NULL)
		root->tail = NULL;
	if(root->head != NULL)
		root->head->prev = NULL;
	return data;
}

void deque_clear(deque* root)
{
	while(root->head){
		list* tmp = root->head;
		root->head = root->head->next;
		free(tmp);
	}
	root->tail = NULL;
}
