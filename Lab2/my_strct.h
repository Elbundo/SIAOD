#ifndef MY_STRCT_SENTRY
#define MY_STRCT_SENTRY

typedef struct my_vector{
	int* array;
	int size;
	int max_size;
} vector;

//constructor
vector* v_create();
vector* v_create_random(int);
vector* v_create_from_vector(vector*);
vector* v_create_from_array(int*, int);
//destructor
void v_free(vector*);
//capacity
int v_size(vector*);
int v_max_size(vector*);
void v_resize(vector*, int n);
int v_capacity(vector*);
int v_empty(vector*);
//element access
int v_get(vector*, int);
void v_set(vector*, int, int);
//modifiers
void v_push_back(vector*, int);
int v_pop_back(vector*);
void v_insert(vector*, int, int);
int v_erase(vector*, int);
int v_add(vector*, int, int (*)(int*, int, int));
int v_remove(vector*, int, int (*)(int*, int, int));
//sorting
void v_qsort(vector*);
//search
int v_bsearch(vector*, int);
int v_fsearch(vector*, int);
int v_intersearch(vector*, int);

typedef struct my_btree{
	int key;
	char h;
	struct my_btree *left, *right;
} btree;

char height(btree*);
int bfactor(btree*);
void fixheight(btree*);
btree* rotateright(btree*);
btree* rotateleft(btree*);
btree* balance(btree*);

//constructor
btree* btree_create();
//destructor
void btree_free(btree**);
//modifiers
btree* btree_add(btree*, int);
btree* btree_remove(btree*, int);
//search
int btree_search(btree**, int);

#endif
