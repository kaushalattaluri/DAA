#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define min(a,b) a<b?a:b;
int size;//declaring it at global level makes it available for all functions
int knapsack_weight;//knapsack capacity
bool* global_best;//global best choices
int global_lb;//best global lowerbound
int global_lb_2;
typedef struct Item{
	int profit;
	int weight;
	int idx;
}Item;

typedef struct Node{
	int upper_bound;//best case (fractional)
	int lower_bound;//worst case (0/1)
	int level;//level in the decision tree
	bool flag;//check whether a particular node is selected
	int cp;//current profit i.e profit till the node 
	int cw;//current weight i.e weight till the node
}Node;

typedef struct priority_queue{
	Node* array;
	int queue_size;
}priority_queue;

priority_queue* create_queue(){
	priority_queue* p=(priority_queue* )malloc(sizeof(priority_queue));
	p->array=(Node *)malloc(sizeof(Node)*1000);
	p->queue_size=0;
	return p;
}
void swap(Node *a,Node* b){
	Node temp=*a;
	*a=*b;
	*b=temp;
}

void heapify(priority_queue* p,int idx){
	int left=2*idx+1;
	int right=2*idx+2;
	int smallest=idx;
	if(left < p->queue_size && p->array[smallest].lower_bound >= p->array[left].lower_bound)
		smallest = left;
	if( right< p->queue_size && p->array[smallest].lower_bound >= p->array[right].lower_bound)
		smallest = right;
	if(smallest != idx){
		swap(&p->array[smallest],&p->array[idx]);
		heapify(p,smallest);
	}
}



//To insert an element into the priority_queue
void insert(priority_queue* p,Node ele){
	p->queue_size++;
	int idx=p->queue_size-1;
	while(idx > 0 && ele.lower_bound >= p->array[(idx-1)/2].lower_bound){
		p->array[idx]=p->array[(idx-1)/2];
		idx=(idx-1)/2;
	}	
	p->array[idx]=ele;
}

//To remove the min element from the priority_queue
void remove_(priority_queue* p){
	swap(&p->array[0],&p->array[p->queue_size-1]);
	p->queue_size--;
	heapify(p,0);
}

void sort(Item* arr){
	int i,j;
	for(i=0;i<size;i++){
		for(j=i+1;j<size;j++){
			if((double)arr[i].profit/arr[i].weight < (double)arr[j].profit/arr[j].weight){
				Item temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
		}
	}
}
//To calculate upper_bound ; it includes fractional weights too
int calculate_upper_bound(int cp,int cw,int idx,Item* arr){
	int profit=cp;
	int weight=cw,i;
	for(i=idx;i<size;i++){
		if(weight+arr[i].weight <= knapsack_weight){
			weight+=arr[i].weight;
			profit-=arr[i].profit;
		}
		else{
			profit-=(double)(knapsack_weight-weight)/arr[i].weight*arr[i].profit;
			break;
		}
	}
	return profit;
}

//To calculate lower bound ; it doesn't include fractional weights 
int calculate_lower_bound(int cp,int cw,int idx,Item* arr){
	int profit=cp;
	int weight=cw,i;
	for(i=idx;i<size;i++){
		if(weight+arr[i].weight <= knapsack_weight){
			weight+=arr[i].weight;
			profit-=arr[i].profit;
		}
		else{
			break;
		}
	}
	return profit;
}

//To solve the knapsack problem
void knapsack(Item* arr){
	sort(arr);
	//create a priority queue which arranges Nodes based on lowerbound
	priority_queue* p=create_queue();
	Node current,left,right;//Current -> parent left,right -> children
	current.upper_bound=current.lower_bound=current.cp=current.cw=current.level=current.flag=0;
	bool selection[size];//To store the path
	int i;
	global_best=(bool *)malloc(sizeof(bool)*(size+1));
	for(i=0;i<size;i++) selection[i]=false; // Initially no items are selected
	insert(p,current);//Insert the dummy first node

/*	uncomment this to check the sorted order of the items
	for(i=0;i<size;i++) printf("idx = %d weight = %d profit =%d\n",arr[i].idx,arr[i].weight,arr[i].profit);
*/
	while(p->queue_size != 0){
		current=p->array[0];//Get the node with minimum lower bound
		remove_(p);
		if((current.upper_bound > global_lb || current.upper_bound >= global_lb_2) && current.level!=0){
			//By additionally comparing it with global_lb_2 gives a chance of elimintating equal maximum profit paths
			//you cannot continue;
			continue;
		}
		
		if(current.level!=0)
			selection[current.level-1]=current.flag;
		if(current.level==size){
			//reached the final stage
			//just compare it with the global best ans
			/*
			printf("we are in the endgame now !!\n");
			for(i=0;i<size;i++) selection[i]==0?printf("False "):printf("True ");printf("   max profit = %d \n",current.lower_bound);
			*/
			//The reason I used global_lb_2 instead of global_lb is when the lower_bound of two paths are equal, pick the one that comes first. It helps to get the exact answer as that of DP 0/1 Knapsack 
			if(current.lower_bound < global_lb_2)
				for(i=0;i<size;i++) global_best[arr[i].idx]=selection[i];
			global_lb_2=min(global_lb_2,current.lower_bound);
			continue;
		}
		right.upper_bound=calculate_upper_bound(current.cp,current.cw,current.level+1,arr);
		right.lower_bound=calculate_lower_bound(current.cp,current.cw,current.level+1,arr);;
		right.flag=false;
		right.level=current.level+1;
		right.cp=current.cp;
		right.cw=current.cw;
		global_lb=min(global_lb,right.lower_bound);
		if(current.cw+arr[current.level].weight <= knapsack_weight){
			//we can add this item to the knapsack
			/*
				include the item and increase its weight and profit and proceed to call lower and upper bound functions on next elements of the array
			*/
			left.upper_bound=calculate_upper_bound(current.cp-arr[current.level].profit,current.cw+arr[current.level].weight,current.level+1,arr);
			left.lower_bound=calculate_lower_bound(current.cp-arr[current.level].profit,current.cw+arr[current.level].weight,current.level+1,arr);
			left.flag=true;
			left.level=current.level+1;
			left.cw=current.cw+arr[current.level].weight;
			left.cp=(current.cp-arr[current.level].profit);
			global_lb=min(global_lb,left.lower_bound);
		}
		else{
			left.lower_bound=left.upper_bound=0;//We are setting it to 0 to eliminate the node
			left.level++;
		}
		
	   	/*uncomment to know the details of the current level items
		  printf("current level= %d current lower bound=%d current.upper_bound=%d cp=%d cw=%d flag=%d\n",current.level,current.lower_bound,current.upper_bound,current.cp,current.cw,current.flag);
		  printf("left.lower_bound= %d left.level=%d left.upper_bound = %d right.lowerbound=%d right.level = %d right.upper_bound=%d\n",left.lower_bound,left.level,left.upper_bound,right.lower_bound,right.level,right.upper_bound);
		  printf("left.cp = %d left.cw=%d right.cp = %d right.cw=%d\n\n",left.cp,left.cw,right.cp,right.cw);
		*/
		if(right.upper_bound <= global_lb&& global_lb!=0) insert(p,right);
		if(left.upper_bound <= global_lb && global_lb!=0) insert(p,left);
	
	}
	printf("The elements taken into the knapsack are \n");
	for(i = 0 ; i< size; i++) global_best[i]==0?printf("0 "):printf("1 ");printf("\n");
	printf("Maximum profit is %d",-global_lb_2);
	free(p->array);free(global_best);
}
	
int main(){
	int i;
	printf("Enter the no. of items\n");
	scanf("%d",&size);
	printf("Enter the details of the items\n");
	Item arr[size];
	for(i=0;i<size;i++){
		printf("Enter the weight and profit of the item : %d\n",i+1);
		scanf("%d%d",&arr[i].weight,&arr[i].profit);
		arr[i].idx=i;
	}
	printf("Enter the knapsack capacity\n");
	scanf("%d",&knapsack_weight);
	global_lb=global_lb_2=0;
	knapsack(arr);
	return 0;
}
