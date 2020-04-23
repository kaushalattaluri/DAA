#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
long min(long a,long b){
	return a<b?a:b;
}
int main(){
	int n,i,j,k;
	printf("Enter the no. of nodes\n");
	scanf("%d",&n);
	printf("Enter the adjacency matrix\n");
	long arr[n][n];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
		      scanf("%ld",&arr[i][j]);
		      if(arr[i][j]==0 && i!=j) arr[i][j]=INT_MAX;
		}
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(i==k || j==k) continue;
				arr[i][j]=min(arr[i][j],arr[i][k]+arr[k][j]);
			}
		}
		printf("Iteration no: %d \n",k+1);
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(arr[i][j]==INT_MAX) printf("INF     ");
				else printf("%ld\t",arr[i][j]);
			}
			printf("\n");
		}	
	}
	printf("Final matrix \n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(arr[i][j]==INT_MAX) printf("INF     ");
			printf("%ld\t",arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}

