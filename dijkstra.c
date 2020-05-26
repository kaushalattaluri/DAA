/*
 	Single source shortest path i.e., shortest path from one vertex to all other vertices
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>
#define INF INT_MAX
long long min(long long a, long long b){
	return a < b ? a : b;
}


void print_path ( long long distance[], int n, int path[], int src ){
	int i;
	for ( i = 0;i < n; i++){
		printf("Minimum distance from %d to %d is %lld  Path is :",src, i, distance[i]);
		int vertex = i;
		while ( path[vertex] != -1 ){
			printf ("%d <- ",vertex);
			vertex = path[vertex];
		}
		if ( distance[i] != INT_MAX) printf(" %d\n",src);
	}
}

void dijkstra(int **arr, int n , int src){
	//distance array of size n
	long long distance[n];
	bool visited[n];
	int i,j, path[n];
	for ( i = 0; i < n; i++){
	       distance[i] = INT_MAX;
	       visited[i] = false;
	       path[i] = -1;
	}

	distance[src] = arr[src][src];
	int count = 0;
	int prev = -1;
	while ( count < n){
		//pick the least cost vertex
		int vertex=-1;int curr_cost = INT_MAX;

		for ( i = 0; i < n ;i++ ){

			//pick only those vertices which are not covered
			if ( !visited[i] && distance[i] < curr_cost){
				curr_cost = distance[i];
				vertex = i;
			}
		}

		if ( vertex == -1) continue;

		visited[vertex] = true;
		for ( i = 0 ; i < n ; i++){

			if ( arr[vertex][i] != INT_MAX && !visited[i]){
				distance[i] = min(distance[i] , curr_cost + arr[vertex][i] );
			}
		}
		count++;
		path[vertex] = prev;
		prev = vertex;
	}
	print_path(distance , n , path , src);
}	



int main(){
	int n, i, j, src;
	printf("Enter the no. of vertices\n");
	scanf("%d",&n);
	int **arr=(int **)malloc(sizeof(int* ) * n);
	for( i = 0 ; i < n ; i++) arr[i]=(int *)malloc(sizeof(int) * n);
	printf("Enter the cost matrix\nNOTE: Enter 0 if there is no path between two vertices\n");

	for (i = 0 ; i < n; i++ ){
		for ( j = 0 ; j < n; j++){
			scanf("%d",&arr[i][j]);
			if(arr[i][j] == 0 && i!=j) arr[i][j] = INT_MAX;
		}
	}

	printf("Enter the source vertex\n");
	scanf("%d",&src);
	dijkstra(arr, n, src);
	return 0;
}
