#ifndef HASH_H_SENTRY
#define HASH_H_SENTRY

typedef struct integer{
	int key;
	struct integer* next;
} my_int;

typedef struct hashtable{
	my_int **data;
	int capacity; 
	int size;
} my_htable;

my_htable* htable_create(int);
void htable_add(my_htable*, int, int (*)(int, int));
void htable_add_chains_method(my_htable*, int);
int htable_contains_key(my_htable*, int, int (*)(int, int));
int htable_contains_key_chains_method(my_htable*, int);
void htable_remove(my_htable*, int, int (*)(int, int));
void htable_remove_chains_method(my_htable*, int);
int hash(int, int);
int simple_rehash(int, int);
int rand_rehash(int, int);

#endif
