#include <stdio.h>

int main()
{
	int board[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {15, 14, 13, 0}};
	int sum = 0, e = 0, count = 0;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(board[i][j] == 0){
				e = i;		
			}else{
				int col = j;
				count = 0;
				for(int m = i; m < 4; m++){
					for(int n = col; n < 4; n++){
						if(board[i][j] > board[m][n] && board[m][n] != 0){
							count++;
						}
					}
					col = 0;
				}
				sum += count;
			}
		}
	}
	sum += e;
	if(sum % 2 != 0){
		printf("Has not solve!\n");
	}else{
		printf("Has solve!\n");
	}
	return 0;
}
