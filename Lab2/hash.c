#include <stdlib.h>
#include <stddef.h>
#include "hash.h"

my_htable* htable_create(int size)
{
	my_htable* htable = malloc(sizeof(my_htable));
	htable->data = malloc(sizeof(my_int) * size);
	for(int i = 0; i < size; i++)
	{
		htable->data[i] = NULL;
	}
		htable->capacity = 0;
		htable->size = size;
	return htable;
}

void htable_add(my_htable* htable, int key, int (*rehash)(int, int))
{
	my_int* new_key = malloc(sizeof(my_int));
	new_key->key = key;
	new_key->next = NULL;
	int h = hash(key, htable->size);
	srand(h);
	while(htable->data[h] != NULL)
		h = rehash(h, htable->size);
	htable->data[h] = new_key;
	htable->capacity++;
}

void htable_add_chains_method(my_htable* htable, int key)
{
	my_int* new_key = malloc(sizeof(my_int));
	new_key->key = key;
	new_key->next = NULL;
	int h = hash(key, htable->size);
	if(htable->data[h] == NULL){
		htable->data[h] = new_key;
	}else{
		my_int* place = htable->data[h];
		new_key->next = place;
		htable->data[h] = new_key;
	}
}

int htable_contains_key(my_htable* htable, int key, int (*rehash)(int, int))
{
	int h = hash(key, htable->size);
	srand(h);
	while(htable->data[h] != NULL){
		if(htable->data[h]->key == key)
			return 1;
		h = rehash(h, htable->size);
	}
	return 0;
}

int htable_contains_key_chains_method(my_htable* htable, int key)
{
	int h = hash(key, htable->size);
	my_int* place = htable->data[h];
	while(place != NULL){
		if(place->key == key)
			return 1;
		place = place->next;
	}
	return 0;
}

void htable_remove(my_htable* htable, int key, int (*rehash)(int, int))
{
	int h = hash(key, htable->size);
	srand(h);
	while(htable->data[h]->key != key && htable->data[h] != NULL)
		h = rehash(h, htable->size);
	int prev;
	while(htable->data[h] != NULL){
		prev = h;
		h = rehash(h, htable->size);
		if(htable->data[h] == NULL)
			break;
		htable->data[prev]->key = htable->data[h]->key;
	}
	free(htable->data[prev]);
	htable->data[prev] = NULL;
}

void htable_remove_chains_method(my_htable* htable, int key)
{
	int h = hash(key, htable->size);
	my_int* place = htable->data[h]->next;
	free(htable->data[h]);
	htable->data[h] = place;
}

int hash(int key, int size)
{
	int h = key % size;
	return h < 0 ? -h : h;
}

int simple_rehash(int hash, int size)
{
	return (hash + 1) % size;
}

int rand_rehash(int hash, int size)
{
	return rand() % size;
}
