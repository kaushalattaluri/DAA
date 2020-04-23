#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef struct element{
	int weight;
	int profit;
}element;

int max(int a,int b){ return a>b?a:b;}

void print_path(element* ele,int** arr,int size,int weight){
	int i=size,j=weight,profit=0;
	bool present[size+1];
	while(i>0 && j>0){
		if(arr[i][j] != arr[i-1][j]){
			present[i]=true;
			j-=ele[i].weight;
			profit+=ele[i].profit;
		}
		else present[i]=false;
		i--;
	}
	printf("The elements taken into the knapsack are\n");
	for(i=1;i<=size;i++) printf("%d ",present[i]);
	printf("\nTotal profit is %d\n",profit);
}
	
			
void knapsack_0_1(element* ele,int weight,int size){
	int i,j;
	int **arr=(int **)malloc(sizeof(int *)*(size+1));
	for(i=0;i<=size;i++) arr[i]=(int *)malloc(sizeof(int)*(weight+1));
	for(i=0;i<=size;i++) arr[i][0]=0;
	for(i=0;i<=weight;i++) arr[0][i]=0;
	for(i=1;i<=size;i++){
		for(j=1;j<=weight;j++){
			if(ele[i].weight > j) arr[i][j]=arr[i-1][j];
			else arr[i][j]=max(arr[i-1][j],ele[i].profit+arr[i-1][j-ele[i].weight]);
		}
	}
	print_path(ele,arr,size,weight);
}
int main(){
	int n,i,weight,profit;
	printf("Enter the no. of elements\n");
	scanf("%d",&n);
	element* arr=(element *)malloc(sizeof(element)*(n+1));
	for(i=1;i<=n;i++){
		printf("Enter the weight and profit of the item %d\n",i);
		scanf("%d%d",&arr[i].weight,&arr[i].profit);
	}
	printf("Enter the knapsack capacity\n");
	scanf("%d",&weight);
	knapsack_0_1(arr,weight,n);
	return 0;
}
