#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct edge{
	int src;
	int dest;
	long weight;
}edge;
void print_path(int* parent,int vertex){
	while(parent[vertex]!=vertex){
		printf("%d <- ",vertex);
		vertex=parent[vertex];
	}
	printf(" %d\n",parent[vertex]);
}
void Bellman_Ford(edge* arr,int source,int vertices,int edges){
	int i,j,k;
	long distance[vertices];int parent[vertices];
	for(i=0;i<vertices;i++){ distance[i]=INT_MAX; parent[i]=i;}
	distance[source]=0;
	for(i=0;i<vertices;i++){
		for(j=0;j<edges;j++){
			if(distance[arr[j].dest] >( distance[arr[j].src] + arr[j].weight)){
				distance[arr[j].dest]=distance[arr[j].src] + arr[j].weight;
				parent[arr[j].dest]=arr[j].src;
			}
		}
	}
	for(i=0;i<edges;i++)
			if(distance[arr[i].dest] >( distance[arr[i].src] + arr[i].weight)){
				printf("There exists a negative cycle\n");
				return ;
	}	
	for(i=0;i<vertices;i++){
			printf("vertex: %d distance: %ld\t path:\t ",i,distance[i]);
			print_path(parent,i);	
	}
}
void main(){
	int v,e,i,j,source;
	printf("Enter the no. of vertices\n");
	scanf("%d",&v);
	printf("Enter the no. of edges\n");
	scanf("%d",&e);
	edge arr[e];
	for(i=0;i<e;i++){
		printf("Enter the source ,destination, and weight of the edge\n");
		scanf("%d%d%ld",&arr[i].src,&arr[i].dest,&arr[i].weight);
	}
	printf("Enter the source vertex\n");
	scanf("%d",&source);
	Bellman_Ford(arr,source,v,e);
}
