#ifndef MY_DEQUE_H_SENTRY
#define MY_DEQUE_H_SENTRY


typedef struct my_deque{
	char* data;
	struct my_deque *next, *prev;
} list;

typedef struct deque_head{
	list* head;
	list* tail;
} deque;

deque* create_deque();
int deque_is_empty(deque*);
void deque_push_back(deque*, char*);
void deque_push_front(deque*, char*);
char* deque_pop_back(deque*);
char* deque_pop_front(deque*);
void deque_clear(deque*);
#endif
