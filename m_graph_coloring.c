#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int vertices,i,m_colors;
int *colors;
int count;
//vertices is declared globally so that every function can now access vertices variable without needing to be passed as parameter

bool is_safe(int vertex,int vertex_color,bool** graph){
	
    for(i=0;i<vertex;i++){
        if(graph[i][vertex] && colors[i] == vertex_color) 
            return false;
    }
    return true;
}

void print(int colors[]){
    printf("Colored board is \n");
    for(i=0;i<vertices;i++){
        printf("%d ",colors[i]+1);
    }
    count++;
    printf("\n");
}

void graph_color(int vertex, bool** graph){
	
	//all vertices are colored
    if(vertex==vertices){
        print(colors);
        return;
    }
    
    int color;
    for(color = 0; color < m_colors; color++){
        if(is_safe(vertex,color,graph)){
        	
			colors[vertex]=color;
            graph_color(vertex+1, graph);
            
        }
    }
}
int main(){
    printf("Enter the no. of vertices\n");
    scanf("%d",&vertices);
    printf("Enter the no. of colors\n");
    scanf("%d",&m_colors);
    int j;
    bool** adjacency_matrix=(bool **)malloc(sizeof(bool *)*vertices);
    for(i=0;i<vertices;i++) adjacency_matrix[i]=(bool *)malloc(sizeof(bool)*vertices);
    printf("Enter the adjacency matrix for the graph\n");
    for(i=0;i<vertices;i++){
        for(j=0;j<vertices;j++)
            scanf("%d",&adjacency_matrix[i][j]);
    }
    colors = (int *)calloc(vertices,sizeof(int));
    graph_color(0,adjacency_matrix);
    if(count == 0) printf("%d coloring for the graph is not possible \n",m_colors);
    free(colors);
    return 0;

}
