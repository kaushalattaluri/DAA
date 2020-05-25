/*
	J Uday Kumar Reddy
	1602-18-737-055
	Travelling Salesman Problem using branch and bound
*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#define INF INT_MAX
#define min(a,b) a<b?a:b
int n;//no. of vertices
long least_cost;
long** cost;//adjacency matrix

//you can do the entire program without using pointers and predefining maxN, which consumes the same spaces for n=5 and n=100. So, instead i used pointers to make it compatible with any n
typedef struct Node{
	int level;//To know the no. of cities visited
	int* path;//To store the path 
	long** red_mat;//reduced matrix
	long val;//To store the cost
}Node;

//for storing the best paths
typedef struct path{
	int* path_arr;
	long val;
}path;

//The reason of using stacks is to hold multiple same valued paths
path* stack;
int top;

//Pushing a path into the stack
void push(int* path_){
	int i;++top;
	for(i=0;i<n;i++) stack[top].path_arr[i]=path_[i];
	stack[top].path_arr[n]=path_[0];
}

//removing a path 
void pop(){
	--top;
}

//returns the cost of the top element int
long top_cost(){
	return stack[top].val;
}

//priority queue to pick the next node based on the val
typedef struct priority_queue{
	int queue_size;
	Node** array;
}priority_queue;


priority_queue* create_pq(){
	priority_queue* temp=(priority_queue* )malloc(sizeof(priority_queue));
	temp->queue_size=0;
	temp->array=(Node **)malloc(sizeof(Node*)*1000);
	return temp;
}

Node * create_node(){
	Node *temp=(Node *)malloc(sizeof(Node));
	temp->level=0;
	temp->path=(int *)malloc(sizeof(int)*n);
	int i;
	temp->val=0;
	for(i=0;i<n;i++) temp->path[i]=-1;
	temp->red_mat=(long **)malloc(sizeof(long *)*n);
	for(i=0;i<n;i++) temp->red_mat[i]=(long *)malloc(sizeof(long)*n);
	return temp;
}

//Copying structures (which contains pointers) using = operator is useless coz it copies the address of the pointer
//instead use this nodecpy that copies the data hold by those items
void nodecpy(Node *dest,Node *src){
	dest->level=src->level;
	int i,j;
	for(i=0;i<n;i++) dest->path[i]=src->path[i];
	for(i=0;i<n;i++) for(j=0;j<n;j++) dest->red_mat[i][j]=src->red_mat[i][j];
	dest->val=src->val;
}

void swap(Node *a,Node* b){
	Node* temp=create_node();
	nodecpy(temp,a);
	nodecpy(a,b);
	nodecpy(b,temp);
}

void destroy_node(Node *a){
	free(a->path);
	int i;
	for(i=0;i<n;i++) free(a->red_mat[i]);
}

void heapify(priority_queue* p,int idx){
	int left=2*idx+1;
	int right=2*idx+2;
	int smallest=idx;
	if(left < p->queue_size && p->array[smallest]->val >= p->array[left]->val)
		smallest = left;
	if( right< p->queue_size && p->array[smallest]->val >= p->array[right]->val)
		smallest = right;
	if(smallest != idx){
		swap(p->array[smallest],p->array[idx]);
		heapify(p,smallest);
	}
}

//To insert an element into the priority_queue
void insert(priority_queue* p,Node* ele){
	p->queue_size++;
	int idx=p->queue_size-1;
	p->array[idx]=create_node();
	while(idx > 0 && ele->val < p->array[(idx-1)/2]->val){
		nodecpy(p->array[idx],p->array[(idx-1)/2]);//equivalent to p->array[idx]=p->array[(idx-1)/2];
		idx=(idx-1)/2;
	}	
	nodecpy(p->array[idx],ele);
}

//To remove the min element from the priority_queue
void remove_(priority_queue* p){
	swap(p->array[0],p->array[p->queue_size-1]);
	p->queue_size--;
	destroy_node(p->array[p->queue_size]);
	heapify(p,0);
}

//find the min element along a row
long row_min(long **arr,int row){
	int i,j;
	long min_=INF;
	for(i=0;i<n;i++)
		min_=min(min_,arr[row][i]);
	return min_;
}

//find the max element along a row
long col_min(long** arr,int col){
	int i,j;
	long min_=INF;
	for(i=0;i<n;i++)
		min_=min(min_,arr[i][col]);
	return min_;
}

//row reduction
void update_row(long** arr,int row,long* red_cost){
	int i,j;
	long min_=row_min(arr,row);
//	printf("row %ld %ld\n",min_,*red_cost);
	if(min_==INF) return;
	*red_cost += min_;
	for(i=0;i<n;i++)
		if(arr[row][i]!=INF)
			arr[row][i]=arr[row][i]-min_;
}
	
//col reduction	
void update_col(long** arr,int col,long* red_cost){
	int i,j;
	long min_=col_min(arr,col);
//	printf("col %ld%ld\n",min_,*red_cost);
	if(min_==INF) return;
	*red_cost += min_;
	for(i=0;i<n;i++)
		if(arr[i][col]!=INF)
			arr[i][col]=arr[i][col]-min_;
}	


void copyarr(long** a,long** b){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			a[i][j]=b[i][j];
	}
}

void display_path(int* path){
	int i=0;printf("Path is ");
	while(i<n && path[i]!=-1) printf("%d ",path[i++]+1);
	printf("\n");
}

void display_arr(long** arr){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++) 
			arr[i][j]==INF?printf("INF     "):printf("%ld\t",arr[i][j]);
		printf("\n");
	}
}


void TSP(){
	least_cost=INF;
	int row,col,i,j;
	
	//creating stack
	stack=(path *)malloc(sizeof(path)*100);
	for(i=0;i<100;i++) stack[i].path_arr=(int *)malloc(sizeof(int)*(n+1));
	top=-1;
	
	Node* current=create_node();
	current->level=0;
	copyarr(current->red_mat,cost);
	//reducing the initial matrix
	for(i=0;i<n;i++)
		update_row(current->red_mat,i,&(current->val));
	for(i=0;i<n;i++)
	update_col(current->red_mat,i,&(current->val));
	
	current->path[0]=0;
	priority_queue* pq=create_pq();
	insert(pq,current);
	bool selection[n];
	while(pq->queue_size){
		//current=pq->array[0]
		nodecpy(current,pq->array[0]);
		//removing first node from the priority queue
		remove_(pq);
		
		//best_cost -> all nodes covered. If current->val > best_cost, then don't explore that node as we cannot get the least path
		if(current->val > least_cost) continue;
		
		//Covered all nodes as we took initial->level = 0 so last node will have n-1 th level
		if(current->level == n-1){
			//popping out those paths whose val is not the least
			while(top>=0 && stack[top].val > current->val) pop();
			//pushing the current path into the stack
			push(current->path);
			stack[top].val=current->val;
			least_cost=current->val;
		}
		
		
		for(i=0;i<n;i++) selection[i]=true;
		for(i=0;i<n;i++) if(current->path[i]!=-1) selection[current->path[i]]=false;
		
		int level=current->level+1;
		int parent=current->path[level-1];
		//uncomment to know the details of the current node
		printf("\nExploring parent node \n");
		display_path(current->path);
		display_arr(current->red_mat);printf("Cost is %ld\n\n",current->val);
		
		
		for(i=0;i<n;i++){
			//looking for the next node. Next node cannot be parent node.
			if(selection[i] && i!=parent){
				int child=i;
				Node* temp=create_node();
				nodecpy(temp,current);
				temp->val=0;
				temp->level=level;
				temp->path[level]=i;
				for(j=0;j<n;j++) temp->red_mat[parent][j]=INF;
				for(j=0;j<n;j++) temp->red_mat[j][child]=INF;
				temp->red_mat[parent][child]=temp->red_mat[child][parent]=INF;
				
				for(j=0;j<level;j++) temp->red_mat[child][temp->path[j]]=INF;
				
				for(j=0;j<n;j++)
					update_row(temp->red_mat,j,&temp->val);
				printf("Row reduction cost is %ld\n",temp->val);	
				for(j=0;j<n;j++)
					update_col(temp->red_mat,j,&temp->val);
				printf("Column reduction cost is %ld\n",temp->val);
				temp->val+=current->val+current->red_mat[parent][child];
				
				//Insert the node into the priority queue
				insert(pq,temp);
				
				//uncomment to see the path and adjacency matrix at a particular stage
				display_path(temp->path);
				display_arr(temp->red_mat);printf("Cost is %ld\n\n",temp->val);
				
			}
		}
	}		
	printf("Least cost path is/are \n");
	for(i=0;i<=top;i++){
		for(j=0;j<n;j++) printf("%d -> ",stack[i].path_arr[j]+1);
		printf("%d\n",stack[i].path_arr[j]+1);	
	}
	
	printf("Minimum cost is %ld\n",least_cost);
	
	//free the stack elements 
	for(i=0;i<100;i++) free(stack[i].path_arr);
	
}
int main(){
	int i,j,k;
	printf("Enter the no. of vertices\n");
	scanf("%d",&n);
	cost=(long **)malloc(sizeof(long* )*n);
	for(i=0;i<n;i++) cost[i]=(long *)malloc(sizeof(long)*n);
	printf("Enter the cost matrix\n");
	printf("Note : Enter cost as 0 if there is no path\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			scanf("%ld",&cost[i][j]);
			if(cost[i][j]==0) cost[i][j]=INF; 
		}
	}
	TSP();

	for(i=0;i<n;i++) free(cost[i]);
	return 0;
}
	
	
