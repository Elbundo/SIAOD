#ifndef HASH_H_SENTRY
#define HASH_H_SENTRY

typedef struct integer{
	int value;
} my_int;

typedef struct hashtable{
	my_int key;
	int capacity; 
	int size;
	int max_size;
} my_htable;

#endif
