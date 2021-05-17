#include "my_strct.h"
#include "mysearch.h"
#include "../Lab1/mysort.h"
#include <stdlib.h>

vector* v_create()
{
	vector *vec = (vector*)malloc(sizeof(vector));
	vec->array = (int*)malloc(sizeof(int));
	vec->size = 0;
	vec->max_size = 1;
	return vec;
}

vector* v_create_random(int n)
{
	vector *vec = (vector*)malloc(sizeof(vector));
	vec->array = (int*)malloc(n*sizeof(int));
	vec->size = n;
	vec->max_size = n;
	for(int i = 0; i < n; i++)
		vec->array[i] = rand() % (10*n);
	return vec;
}

void v_free(vector* vec)
{
	free(vec->array);
	free(vec);
	vec = NULL;
}

int v_size(vector* vec)
{
	return vec->size;
}

int v_max_size(vector* vec)
{
	return vec->max_size;
}

void v_resize(vector* vec, int n)
{
	int *buf = vec->array;
	vec->array = (int*)malloc(n*sizeof(int));
	for(int i = 0; i < n; i++){
		if(i >= vec->max_size)
			vec->array[i] = 0;
		else
			vec->array[i] = buf[i];
	}
	if(vec->size > n)
		vec->size = n;
	vec->max_size = n;	
}

int v_capacity(vector* vec)
{
	return vec->max_size - vec->size;
}

int v_empty(vector* vec)
{	
	return vec->size;
}

int v_get(vector* vec, int i)
{
	return vec->array[i];
}

void v_set(vector* vec, int i, int key)
{
	vec->array[i] = key;
}

int v_add(vector *vec, int key, int (*find)(int*, int, int))
{
	int i = find(vec->array, v_size(vec), key);
	if(i < v_size(vec) && v_get(vec, i) == key)
		return 0;
	v_insert(vec, i, key);
	return 1;
}

int v_remove(vector *vec, int key, int (*find)(int*, int, int))
{
	int i = find(vec->array, v_size(vec), key);
	if(i == -1)
		return 0;
	v_erase(vec, i);
	return 1;
}

void v_push_back(vector *vec, int key)
{
	if(vec->size >= vec->max_size){	
		int *buf = vec->array;
		vec->max_size *= 2;
		vec->array = (int*)malloc(vec->max_size*sizeof(int));
		for(int i = 0; i < vec->size; i++)
			vec->array[i] = buf[i];
		free(buf);
	}
	vec->array[vec->size] = key;
	vec->size++;
}

int v_pop_back(vector *vec)
{
	if(vec->size == 0)
		return -1;
	vec->size--;
	return vec->array[vec->size];
}

void v_insert(vector *vec, int pos, int key)
{
	if(vec->size >= vec->max_size){
		int *buf = vec->array;
		vec->max_size *= 2;
		vec->array = (int*)malloc(vec->max_size*sizeof(int));
		for(int i = 0; i < vec->size; i++)
			vec->array[i] = buf[i];
		free(buf);
	}
	vec->size++;
	for(int i = 0; i < vec->size - pos; i++)
		vec->array[vec->size - i] = vec->array[vec->size - i - 1];
	vec->array[pos] = key;	
}

int v_erase(vector *vec, int pos)
{
	int key = vec->array[pos];
	vec->size--;
	for(int i = pos; i < vec->size; i++)
		vec->array[i] = vec->array[i + 1];
	return key;
}

void v_qsort(vector* vec)
{
	inc_qsort(vec->array, vec->size);	
}

int v_bsearch(vector* vec, int key)
{
	return my_bsearch(vec->array, vec->size, key);
}

int v_fsearch(vector* vec, int key)
{
	return my_bsearch(vec->array, vec->size, key);
}

int v_intersearch(vector *vec, int key)
{
	return my_intersearch(vec->array, vec->size, key);
}


/*Binary Tree*/

char height(btree *root)
{
	return root?root->h:0;
}

int bfactor(btree *root)
{
	return height(root->right) - height(root->left);
}

void fixheight(btree *root)
{
	char hl = height(root->left);
	char hr = height(root->right);
	root->h = (hl > hr ? hl : hr) + 1;
}

btree* rotateright(btree *root)
{
	btree *newroot = root->left;
	root->left = newroot->right;
	newroot->right = root;
	fixheight(root);
	fixheight(newroot);
	return newroot;
}

btree* rotateleft(btree *root)
{
	btree *newroot = root->right;
	root->right = newroot->left;
	newroot->left = root;
	fixheight(root);
	fixheight(newroot);
	return newroot;
}

btree* balance(btree *root)
{
	fixheight(root);
	if(bfactor(root) == 2){
		if(bfactor(root->right) < 0)
			root->right = rotateright(root->right);
		return rotateleft(root);
	}
	if(bfactor(root) == -2){
		if(bfactor(root->left) > 0)
			root->left = rotateleft(root->left);
		return rotateright(root);
	}
	return root;
}

btree* btree_add(btree *root, int key)
{
	if(!root){
		root = (btree*)malloc(sizeof(btree));
		root->key = key;
		root->h = 1;
		root->left = NULL;
		root->right = NULL;
		return root;
	}
	if(root->key == key)
		return root;
	if(root->key > key)
		root->left = btree_add(root->left, key);
	else
		root->right = btree_add(root->right, key);
	return balance(root);
}

btree* findmin(btree *root)
{
	return root->left ? findmin(root->left) : root;
}

btree* removemin(btree* root)
{
	if(root->left == NULL)
		return root->right;
	root->left = removemin(root->left);
	return balance(root);
}

btree* btree_remove(btree* root, int key)
{
	if(!root) return NULL;
	if(root->key > key){
		root->left = btree_remove(root->left, key);
	}else if(root->key < key){
		root->right = btree_remove(root->right, key);
	}else{
		btree *l = root->left;
		btree *r = root->right;
		free(root);
		if(!r) return l;
		btree *min = findmin(r);
		min->right = removemin(r);
		min->left = l;
		return balance(min);
	}
	return balance(root);
}

int btree_search(btree **root, int key)
{
	if(!*root){
		return -1;
	}
	if((*root)->key == key)
		return key;
	if((*root)->key > key)
		return btree_search(&(*root)->left, key);
	else
		return btree_search(&(*root)->right, key);
}

void btree_free(btree **root)
{
	if(!*root){
		return;
	}
	btree_free(&(*root)->left);
	btree_free(&(*root)->right);
	free(*root);
	*root = NULL;
}
