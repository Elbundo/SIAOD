#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mysearch.h"
#include "my_strct.h"

#define ARR_LEN 10

int main()
{
	srand(time(NULL));
	vector* vec = NULL;
	vec = v_create();
	for(int i = 0; i < ARR_LEN; i++){
		v_push_back(vec, rand() % ARR_LEN);
	}
	v_qsort(vec);
	for(int i = 0; i < v_size(vec); i++){
		printf("%d ", v_get(vec, i));
	}
	printf("\n");
	v_add(vec, 5, &my_i);
	v_remove(vec, 1, &my_intersearch);
	for(int i = 0; i < v_size(vec); i++){
		printf("%d ", v_get(vec, i));
	}
	printf("\n");
	printf("%d\n", v_bsearch(vec, 5));
	printf("Test binary tree\n");
	btree* my_tree = NULL;
	for(int i = 0; i < v_size(vec); i++){
		btree_add(&my_tree, v_get(vec, i));
	}
	printf("%d\n", btree_search(&my_tree, 1));
	v_free(vec);
	return 0;
}
