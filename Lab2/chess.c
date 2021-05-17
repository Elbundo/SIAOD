#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 8

void show_board(char (*)[N]);
void put_queen(char (*)[N], int, int);
void close_horizontal(char (*)[N], int);
void close_vertical(char (*)[N], int);
void close_diagonal(char (*)[N], int, int);
void copy_board(char (*)[N], char (*)[N]);
int place_queens(char (*)[N], int, int);

int main()
{
	char board[N][N] = {0};
	printf("All variant - %d\n", place_queens(board, 0, 0));	
	return 0;
}

int place_queens(char (*arr)[N], int x, int k)
{
	static int n = 0;
	//printf("place_queens(cp_arr, %d, %d)\n", x, k);
	char cp_arr[N][N] = {0};
	if(k == N){
		n++;
		show_board(arr);
		return n;
	}
	for(int i = 0; i < N; i++){
		if(arr[x][i] == 0){
			copy_board(arr, cp_arr);
			put_queen(cp_arr, x, i);
			place_queens(cp_arr, x + 1, k + 1);
		}
	}
	return n;
}

void show_board(char (*arr)[N])
{	
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if(arr[i][j] == 0)
				printf("%c ", 'o');
			if(arr[i][j] == 1)
				printf("%c ", '/');
			if(arr[i][j] == 2)
				printf("%c ", 'X');
		}
		printf("\n");
	}
	printf("\n");
}

void put_queen(char (*arr)[N], int x, int y)
{
	arr[x][y] = 2;
	close_horizontal(arr, x);
	close_vertical(arr, y);
	close_diagonal(arr, x, y);
}

void close_horizontal(char (*arr)[N], int horizontal)
{
	for(int i = 0; i < N; i++){
		if(arr[horizontal][i] == 0)
			arr[horizontal][i] = 1;
	}
}

void close_vertical(char (*arr)[N], int vertical)
{
	for(int i = 0; i < N; i++){
		if(arr[i][vertical] == 0)
			arr[i][vertical] = 1;
	}
}

void close_diagonal(char (*arr)[N], int x, int y)
{
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			if((x - i) == (y - j) || (i - x) == (j - y) ||
			(x - i) == (j - y) || (i - x) == (y - j)){
				if(arr[i][j] == 0)
					arr[i][j] = 1;
			}
		}
	}
}

void copy_board(char (*from)[N], char (*to)[N])
{
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			to[i][j] = from[i][j];
		}
	}
}
