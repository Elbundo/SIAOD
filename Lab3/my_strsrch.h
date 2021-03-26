#ifndef MY_STRSRCH_SENTRY
#define MY_STRSRCH_SENTRY

typedef struct my_string{
	char* buf;
	int length;
}my_str;

void input_str(my_str*);
int scan_str(char*);


#endif
