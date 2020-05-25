import java.util.*;
class Item{
	float weight;//Weight of the item
	int value;//value of the item
	int idx;//index of the item
	public Item(){}
	public Item(int value,float weight,int idx){
		this.value=value;
		this.weight=weight;
		this.idx=idx;
	}
}

class Node{
	float tv;//total value->sum of the values of the items included 
	float tw;//total weight->sum of the weights of the items included
	float ub;//upper bound->best case (fractional knpsck)
	float lb;//lower bound->worst case (0/1)
	int level;//level of the node in the decision tree
	boolean flag;//to know if the current item is selected or not
	public Node(){}
	public Node(Node cpy){
		this.tv=cpy.tv;
		this.tw=cpy.tw;
		this.ub=cpy.ub;
		this.lb=cpy.lb;
		this.level=cpy.level;
		this.flag=cpy.flag;
	}
	
}

class sortByC implements Comparator<Node>{
	public int compare(Node a,Node b){
		boolean temp=a.lb > b.lb;
		return temp?1:-1;
	}
}

class sortByRatio implements Comparator<Item>{
	public int compare(Item a,Item b){
		boolean temp=(float)a.value/a.weight > (float)b.value/b.weight;
		return temp?-1:1;
	}
}
	
	
class knapsack{
	private static int size;
	private static float capacity;
	
	//To calculate upper bound (includes fractional part of the items)
	static float upperBound(float tv,float tw,int idx,Item arr[]){
		float value=tv;
		float weight=tw;
		for(int i=idx;i<size;i++){
			if(weight+arr[i].weight <= capacity){
				weight+=arr[i].weight;
				value-=arr[i].value;
			}
			else{
				value-=(float)(capacity-weight)/arr[i].weight*arr[i].value;
				break;
			}
		}	
		return value;
	}
	
	//To calculate lower bound (doesn't include fractional part of the items)
	static float lowerBound(float tv,float tw,int idx,Item arr[]){
		float value=tv;
		float weight=tw;
		for(int i=idx;i<size;i++){
			if(weight+arr[i].weight <= capacity){
				weight+=arr[i].weight;
				value-=arr[i].value;
			}
			else{
				break;
			}
		}
		return value;
	}
	
	static void assign(Node a,float ub,float lb,int level,boolean flag,float tv,float tw){
		a.ub=ub;
		a.lb=lb;
		a.level=level;
		a.flag=flag;
		a.tv=tv;
		a.tw=tw;
	}
		
	public static void solve(Item arr[]){
		//sort the items based on the profit/weight ratio
		Arrays.sort(arr,new sortByRatio());
		
		Node current,left,right;
		current=new Node();
		left=new Node();
		right=new Node();
		
		//minLB -> minimum lower bound of all the nodes explored
		//finalLB -> minimum lower bound of all the paths that reached the final level
		float minLB=0,finalLB=Integer.MAX_VALUE;
		current.tv=current.tw=current.ub=current.lb=0;current.level=0;
		current.flag=false;
		PriorityQueue<Node> pq=new PriorityQueue<Node>(new sortByC());
		pq.add(current);
		
		//currPath -> boolean array to know whether an element is included or not
		//finalPath -> boolean array to store the result of selection array when it reached the last level
		boolean currPath[]=new boolean[size];
		boolean finalPath[]=new boolean[size];
		
		while(!pq.isEmpty()){
			current=pq.poll();
			if(current.ub > minLB || current.ub >= finalLB){
				//if the current node's best case value is less than minLB, then there is no reason to explore that node
				//including finalLB eliminates all those paths whose best values is equal to the finalLB
				continue;
			}
			
			if(current.level!=0) currPath[current.level-1]=current.flag;
			
			if(current.level==size){
				if(current.lb < finalLB){
					//Reached last level
					for(int i=0;i<size;i++) finalPath[arr[i].idx]=currPath[i];
					finalLB=current.lb;
				}
				continue;
			}
			
			int level=current.level;
		
			//right node -> without including item in consideration so cp,cw will be that of parent(current)
			assign(right,upperBound(current.tv,current.tw,level+1,arr),lowerBound(current.tv,current.tw,level+1,arr),level+1,false,current.tv,current.tw);

			if(current.tw + arr[current.level].weight <= capacity){
				//left node -> including item in consideratin. c and lb should be calculated including the current item. 
				left.ub=upperBound(current.tv-arr[level].value,current.tw+arr[level].weight,level+1,arr);
				left.lb=lowerBound(current.tv-arr[level].value,current.tw+arr[level].weight,level+1,arr);
				assign(left,left.ub,left.lb,level+1,true,current.tv-arr[level].value,current.tw+arr[level].weight);
			}
			else{
				//left node cannot be inserted. So c and lb are set to 1 to stop the left node from getting added to priority queue
				left.ub=left.lb=1;
			}
			
			//updating minLB
			minLB=Math.min(minLB,left.lb);
			minLB=Math.min(minLB,right.lb);
			
			if(minLB >= left.ub ) pq.add(new Node(left));
			if(minLB >= right.ub) pq.add(new Node(right));
		}
		System.out.println("Items taken into the knapsack are");
		for(int i=0;i<size;i++){
			if(finalPath[i]) System.out.print("1 ");
			else System.out.print("0 ");
		}
		System.out.println("\nMaximum profit is "+(-finalLB));
	}
		
	public static void main(String args[]){
		size=4;
		capacity=15;
		Item arr[]=new Item[size];
		arr[0]=new Item(10,2,0);
		arr[1]=new Item(10,4,1);
		arr[2]=new Item(12,6,2);
		arr[3]=new Item(18,9,3);
		solve(arr);
	}
}
	
