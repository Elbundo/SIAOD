#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>

int* prefix_func(char*);
int KMP(char*, char*);
int BM(char*, char*);
char* scan_str();
double howsec(struct timeval*, struct timeval*);
int isPrefix(char*, char*);
int isSuffix(char*, char*);

int main()
{
	char *string = NULL, *pattern = NULL;
	char c, p; 
	struct timeval begin, end;
	string = scan_str();
	pattern = scan_str();
	printf("Search for the exact phrase?(y/n)\n");
	p = getchar();
	getchar();
	printf("Case sensitive?(y/n)\n");
	c = getchar();
	if(c == 'n'){
		for(int i = 0; i < strlen(string); i++)
			string[i] = tolower(string[i]);
		for(int i = 0; i < strlen(pattern); i++)
			pattern[i] = tolower(pattern[i]);
	}
	if(p == 'y'){
		int length = strlen(pattern);
		char* buf = malloc(length + 3);
		buf[0] = ' ';
		for(int i = 0; i < length; i++){
			buf[i + 1] = pattern[i];
		}
		buf[length + 1] = ' ';
		buf[length + 2] = 0;
		free(pattern);
		pattern = buf;
	}
	printf("%s\n%s\n", string, pattern);
	gettimeofday(&begin, NULL);
	int ind;
	if(p == 'n'){
		ind = KMP(string, pattern);
	}else if(p == 'y'){
		if(isPrefix(string, pattern)){
			ind = 0;
			
		}else if(isSuffix(string, pattern)){
			ind = strlen(string) - strlen(pattern);
		}else{
			ind = KMP(string, pattern);
		}
	}
	printf("KMP - %d, time run - ", ind);
	gettimeofday(&end, NULL);
	printf("%.10f\n", howsec(&begin, &end));
	gettimeofday(&begin, NULL);
	if(p == 'n'){
		ind = BM(string, pattern);
	}else if(p == 'y'){
		if(isPrefix(string, pattern)){
			ind = 0;
			
		}else if(isSuffix(string, pattern)){
			ind = strlen(string) - strlen(pattern);
		}else{
			ind = BM(string, pattern);
		}
	}
	printf("BM - %d, time run - ", ind);
	gettimeofday(&end, NULL);
	printf("%.10f\n", howsec(&begin, &end));
	gettimeofday(&begin, NULL);
	char* ptr;
	if(p == 'n'){
		ptr = strstr(string, pattern);
	}else if(p == 'y'){
		if(isPrefix(string, pattern)){
			ptr = string;
			
		}else if(isSuffix(string, pattern)){
			ptr = string + strlen(string) - strlen(pattern);
		}else{
			ptr = strstr(string, pattern);
		}
	}
	printf("include search - %ld, time run - ",  ptr - string);
	gettimeofday(&end, NULL);
	printf("%.10f\n", howsec(&begin, &end));
	free(pattern);
	free(string);
	return 0;
}

int KMP(char* string, char* pattern)
{
	int k = 0, l = 0, n = strlen(string);
	int* pi = prefix_func(pattern);
	while(k < n){
		if(string[k] == pattern[l]){
			k++;
			l++;
			if(l == strlen(pattern)){
				free(pi);
				return k - l; 
			}
		}else{
			if(l == 0){
				k++;
				if(k == strlen(string)){
					free(pi);
					return -1;
				}
			}else{
				l = pi[l - 1];
			}
		}	
	}
	free(pi);
	return -1;
}

int* prefix_func(char* pattern)
{
	int* pi = malloc(strlen(pattern) * sizeof(int));
	int i = 1, j = 0;
	pi[0] = 0;
	while(i < strlen(pattern)){
		if(pattern[i] == pattern[j]){
			pi[i] = j + 1;
			i++;
			j++;
		}else{
			if(j == 0){
				pi[i] = 0;
				i++;
			}else{
				j = pi[j - 1];
			}
		}
	}
	return pi;
}

int BM(char* string, char* pattern)
{
	int m = strlen(pattern);
	int d[256];
	for(int i = 0; i < 256; i++)
		d[i] = m;
	for(int i = 0; i < m - 1; i++)
		d[(int)pattern[i]] = m - 1 - i;
	int k = m - 1, l = m - 1, n = strlen(string);
	while(k < n){
		if(string[k] == pattern[l]){
			if(l == 0){
				return k;
			}else{
				k--;
				l--;
			}
		}else{
			l = m - 1;
			k += d[(int)string[k]];
		}
	}
	return -1;
}

char* scan_str()
{
	char* str = NULL, *buf = NULL;
	int c = 0, n = 0;
	while((c = getchar()) != '\n'){
		buf = str;
		str = malloc(++n);
		for(int i = 0; i < n - 1; i++)
			str[i] = buf[i];
		str[n - 1] = c;
	}
	buf = str;
	str = malloc(++n);
	for(int i = 0; i < n - 1; i++)
		str[i] = buf[i];
	str[n - 1] = 0;
	return str;
}

double howsec(struct timeval* begin, struct timeval* end)
{
	double sbegin = (double)(begin->tv_sec + (double)begin->tv_usec / 1000000);
	double send = (double)(end->tv_sec + (double)end->tv_usec / 1000000);
	return send - sbegin;
}

int isPrefix(char* string, char* pattern)
{
	for(int i = 0; i < strlen(pattern) - 1; i++)
		if(string[i] != pattern[i + 1])
			return 0;
	return 1;
}

int isSuffix(char* string, char* pattern)
{
	for(int i = 0; i < strlen(pattern) - 1; i++)
		if(string[strlen(string) - 1 - i] != pattern[strlen(pattern) - 1 - i])
			return 0;
	return 1;
}
