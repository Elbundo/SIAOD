#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mysearch.h"
#include "my_strct.h"
#include "hash.h"

#define VEC_SIZE 100000
#define HTABLE_SIZE 300000

double howsec(struct timeval*, struct timeval*);

int main()
{
	srand(time(NULL));	
	vector* vec = NULL;
	vector* vec2 = NULL;
	vector* vec3 = NULL;
	btree* my_tree = NULL;
	btree* my_tree2 = NULL;
	my_htable* simple_htable = NULL;
	my_htable* random_htable = NULL;
	my_htable* chains_htable = NULL;	
	struct timeval begin, end;

	printf("--------------------------Creating------------------------------\n");
	gettimeofday(&begin, NULL);
	vec = v_create_random(VEC_SIZE);
	gettimeofday(&end, NULL);
	printf("Create vector with random data\t\t - \t%.10f sec\n", howsec(&begin, &end));
	
	gettimeofday(&begin, NULL);
	vec2 = v_create();
	for(int i = 0; i < v_size(vec); i++){
		v_push_back(vec2, v_get(vec, i));
	}
	gettimeofday(&end, NULL);
	printf("Filling empty vector\t\t\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	vec3 = v_create();
	for(int i = 0; i < v_size(vec); i++){
		v_add(vec3, v_get(vec, i), &my_b);
	}
	gettimeofday(&end, NULL);
	printf("Filling empty vector with saving sorting - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec); i++){
		my_tree = btree_add(my_tree, v_get(vec, i));
	}
	gettimeofday(&end, NULL);
	printf("Create tree with random data\t\t - \t%.10f sec\n", howsec(&begin, &end));	
	
	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec3); i++){
		my_tree2 = btree_add(my_tree2, v_get(vec3, i));
	}
	gettimeofday(&end, NULL);
	printf("Create tree with sorting data\t\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	simple_htable = htable_create(HTABLE_SIZE);
	for(int i = 0; i < v_size(vec); i++){
		htable_add(simple_htable, v_get(vec, i), &simple_rehash);
	}
	gettimeofday(&end, NULL);
	printf("Create hashtable with simple rehash\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	random_htable = htable_create(HTABLE_SIZE);
	for(int i = 0; i < v_size(vec); i++){
		htable_add(random_htable, v_get(vec, i), &rand_rehash);
	}
	gettimeofday(&end, NULL);
	printf("Create hashtable with random rehash\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	chains_htable = htable_create(HTABLE_SIZE);
	for(int i = 0; i < v_size(vec); i++){
		htable_add_chains_method(chains_htable, v_get(vec, i));
	}
	gettimeofday(&end, NULL);
	printf("Create hashtable with chains method\t - \t%.10f sec\n", howsec(&begin, &end));	
	printf("----------------------------------------------------------------\n\n");

	printf("---------------------------Sorting------------------------------\n");
	gettimeofday(&begin, NULL);
	v_qsort(vec);	
	gettimeofday(&end, NULL);
	printf("Sorting vector\t\t\t\t - \t%.10f sec\n", howsec(&begin, &end));	
	printf("----------------------------------------------------------------\n\n");

	printf("--------------------------Searching-----------------------------\n");
	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec); i++)
		v_bsearch(vec, v_get(vec, i));
	gettimeofday(&end, NULL);
	printf("Binary search\t\t\t\t - \t%.10f sec\n", howsec(&begin, &end));
	
	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec); i++)
		v_fsearch(vec, v_get(vec, i));
	gettimeofday(&end, NULL);
	printf("Fibonacci search\t\t\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec); i++)
		v_intersearch(vec, v_get(vec, i));
	gettimeofday(&end, NULL);
	printf("Interpolation search\t\t\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec); i++)
		btree_search(&my_tree, v_get(vec, i));
	gettimeofday(&end, NULL);
	printf("Binary tree search\t\t\t - \t%.10f sec\n", howsec(&begin, &end));	
	
	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec); i++)
		htable_contains_key(simple_htable, v_get(vec, i), &simple_rehash);
	gettimeofday(&end, NULL);
	printf("Search in hashtable with simple rehash\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec); i++)
		htable_contains_key(random_htable, v_get(vec, i), &rand_rehash);
	gettimeofday(&end, NULL);
	printf("Search in hashtable with random rehash\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec); i++)
		htable_contains_key_chains_method(chains_htable, v_get(vec, i));
	gettimeofday(&end, NULL);
	printf("Search in hashtable with chains method\t - \t%.10f sec\n", howsec(&begin, &end));	
	printf("----------------------------------------------------------------\n\n");

	vector* vec4 = v_create();
	for(int i = 0; i < 100; i++)
		v_push_back(vec4, -(rand() % 1000));
	printf("----------------------------Adding------------------------------\n");
	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		v_push_back(vec, v_get(vec4, i));
	gettimeofday(&end, NULL);
	printf("Add in vector with realloc\t\t - \t%.10f sec\n", howsec(&begin, &end));
	
	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		v_push_back(vec2, v_get(vec4, i));
	gettimeofday(&end, NULL);
	printf("Add in vector without realloc\t\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		v_add(vec3, v_get(vec4, i), &my_b);
	gettimeofday(&end, NULL);
	printf("Add in vector with saving sorting\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		my_tree = btree_add(my_tree, v_get(vec4, i));
	gettimeofday(&end, NULL);
	printf("Add in binary tree\t\t\t - \t%.10f sec\n", howsec(&begin, &end));	
	
	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		htable_add(simple_htable, v_get(vec4, i), &simple_rehash);
	gettimeofday(&end, NULL);
	printf("Add in hashtable with simple rehash\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		htable_add(random_htable, v_get(vec4, i), &rand_rehash);
	gettimeofday(&end, NULL);
	printf("Add in hashtable with random rehash\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		htable_add_chains_method(chains_htable, v_get(vec4, i));
	gettimeofday(&end, NULL);
	printf("Add in hashtable with chains method\t - \t%.10f sec\n", howsec(&begin, &end));	
	printf("----------------------------------------------------------------\n\n");

	printf("---------------------------Removing-----------------------------\n");	
	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		v_pop_back(vec);
	gettimeofday(&end, NULL);
	printf("Remove in vector\t\t\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		v_add(vec3, v_get(vec4, i), &my_bsearch);
	gettimeofday(&end, NULL);
	printf("Remove in vector with saving sorting\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		my_tree = btree_remove(my_tree, v_get(vec4, i));
	gettimeofday(&end, NULL);
	printf("Remove in binary tree\t\t\t - \t%.10f sec\n", howsec(&begin, &end));	
	
	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		htable_add(simple_htable, v_get(vec4, i), &simple_rehash);
	gettimeofday(&end, NULL);
	printf("Remove in hashtable with simple rehash\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		htable_remove(random_htable, v_get(vec4, i), &rand_rehash);
	gettimeofday(&end, NULL);
	printf("Remove in hashtable with random rehash\t - \t%.10f sec\n", howsec(&begin, &end));	

	gettimeofday(&begin, NULL);
	for(int i = 0; i < v_size(vec4); i++)
		htable_remove_chains_method(chains_htable, v_get(vec4, i));
	gettimeofday(&end, NULL);
	printf("Remove in hashtable with chains method\t - \t%.10f sec\n", howsec(&begin, &end));	
	printf("----------------------------------------------------------------\n\n");

	v_free(vec);
	v_free(vec2);
	v_free(vec3);
	btree_free(&my_tree);
	return 0;
}


double howsec(struct timeval* begin, struct timeval* end)
{
	double sbegin = (double)(begin->tv_sec + (double)begin->tv_usec / 1000000);
	double send = (double)(end->tv_sec + (double)end->tv_usec / 1000000);
	return send - sbegin;
}
