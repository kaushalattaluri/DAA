#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define INF INT_MAX
void print_path(int** tracker,int i,int j){
	if(i==j){
		printf("A%d",i);
		return ;
	}
	printf("(");
	print_path(tracker,i,tracker[i][j]);
	print_path(tracker,tracker[i][j]+1,j);
	printf(")");
}
void matrix_mul(int* dimensions,int n){
	int cost[n+1][n+1],i,j,k,len;int** tracker=(int **)malloc(sizeof(int*)*(n+1));
	for(i=0;i<=n;i++) tracker[i]=(int *)malloc(sizeof(int)*(n+1));
	for(i=0;i<=n;i++) for(j=0;j<=n;j++) cost[i][j]=tracker[i][j]=0;

	
	//based on formula ans => cost[i,j] = min ( i <= k < j { m[i,k] + m[k+1 , j]+ p(i-1)*p(k)*p(j) 
	//here we are trying to find cost[1,n]
	//for len = 2 to len <= n => it indicates that we are trying to check for all the possible chain lengths
	//i.e a1 * a2 , a3 * a4  (length two ) , a2 * a3 * a4 (length three )
	
	for(len=2;len<=n;len++){
		for(i=1;i<=n-len+1;i++){
			j=i+len-1;
			cost[i][j]=INF;
			for(k=i;k<j;k++){
				int q=cost[i][k]+cost[k+1][j]+dimensions[i-1]*dimensions[k]*dimensions[j];
				if(q < cost[i][j]){
					cost[i][j]=q;
					tracker[i][j]=k;
				}
			}
		}
		for(int i=1;i<=n;i++){
			for(j=1;j<=n;j++) printf("%d  ",cost[i][j]);
			printf("\n");
		}
	}
	printf("Min scalar multiplications is %d\n",cost[1][n]);
	print_path(tracker,1,n);
}



int main(){
	printf("Enter the  no. of matrices\n");
	int n;
	scanf("%d",&n);
	int p[n+1];
	printf("Enter the dimensions\n");
	printf("Enter the dimensions of the matrix 1\n");
	scanf("%d%d",&p[0],&p[1]);
	for(int i=2,a;i<=n;i++){
		a=p[i-1];
		printf("Enter the dimensions of matrix %d\n",i);
		scanf("%d%d",&p[i-1],&p[i]);
		if(p[i-1] != a){
			printf("Matrix multiplication is not possible\n");
			--i;
			continue;
		}
	}
	matrix_mul(p,n);
	return 0;
}
