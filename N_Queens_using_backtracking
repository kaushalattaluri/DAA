#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
int size;//size of the board
int* board;//1-D array to store the column each queen is placed at
int cnt=0;

//function to return absolute value
int abs(int a){
	return a<0?-a:a;
}

void print_board(){
	int i,j;
	printf("Solution %d is \n",++cnt);
	for(i=0;i<size;i++){ for (j=0;j<size;j++) if(board[i]==j) printf("Q "); else printf("0 "); printf("\n");}
	printf("\n");
}

//to check if the kth queen can be placed in yth column
bool check_safe(int k,int y){
	int i;
	
	//check if any of the previous queens are placed in yth column i.e., board[i] == y
	//check if any of the previously placed queen is in diagonal with the yth column
	for(i=0;i<k;i++) if(board[i]==y || abs(i-k)==abs(y-board[i])) return false;
	return true;
}

void n_queens(int k){
	int i;
	
	//all queens are placed
	if(k==size){
		print_board();
		return ;
	}
	for(i=0;i<size;i++){
		if(check_safe(k,i)){
			//placing kth queen at ith column is safe
			board[k]=i;
			n_queens(k+1);
		}
	}
}
void main(){
	printf("Enter the size of the chess board\n");
	scanf("%d",&size);
	board=(int *)malloc(sizeof(int)*size);
	n_queens(0);
	if(cnt==0) printf("There exists no solution\n");
	free(board);
}



