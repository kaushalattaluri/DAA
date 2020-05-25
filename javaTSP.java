import java.util.*;
class Node{
	int level;//level of the node in the decision tree
	int size;//no. of vertices 
	int path[];//path
	long value;//cost to travel the path
	long reducedMatrix[][];//reduced matrix
	public Node(int size){
		this.size=size;
		level=0;
		path=new int[size];
		for(int i=0;i<size;i++) path[i]=-1;
		reducedMatrix=new long[size][size];
		value=0;
	}
	//we cannot directly copy the contents using = sign 
	public void nodeCpy(Node src){
		this.value=src.value;
		this.level=src.level;
		for(int i=0;i<size;i++) path[i]=src.path[i];
		for(int i=0;i<size;i++) for(int j=0;j<size;j++) reducedMatrix[i][j]=src.reducedMatrix[i][j];
	}
}

//Class to compare nodes based on the values
class sortByValue implements Comparator<Node>{
	public int compare(Node a,Node b){
		if(a.value < b.value) return -1;
		else return 1;
	}
}
	
//Function to solve TSP problem
class TSPBB{
	static int n;//no. of vertices
	static long cost[][];//initial cost matrix
	static long INF;//value of INT_MAX
	
	//class to handle multiple paths 
	static class Path{
		int path[];
		long value;
		public Path(int path[],long value,int size){
			this.path=new int[size+1];
			for(int i=0;i<size;i++) this.path[i]=path[i];this.path[size]=path[0];
			this.value=value;
		}
	}
	
	//method to return the rowReduction cost
	public static long rowReduction(long arr[][]){
		long redCost=0;
		for(int row=0;row<n;row++){
			long min_=INF;
			for(int i=0;i<n;i++) min_=Math.min(min_,arr[row][i]);
			if(min_ == INF) continue;
			for(int i=0;i<n;i++)
				if(arr[row][i] != INF){
					arr[row][i]-=min_;
				}
			redCost+=min_;
		}
		return redCost;
	}
		
	//method to return the colReduction value
	public static long columnReduction(long arr[][]){
		long redCost=0;
		for(int col=0;col<n;col++){
			long min_=INF;
			for(int i=0;i<n;i++) min_=Math.min(min_,arr[i][col]);
			if(min_ == INF) continue;
			for(int i=0;i<n;i++)
				if(arr[i][col] != INF){
					arr[i][col]-=min_;
				}
			redCost+=min_;
		}
		return redCost;
	}
	
	//To display the reducedMatrix
	public static void displayArr(long arr[][]){
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(arr[i][j]!=INF)
					System.out.print(arr[i][j]+"\t");
				else 
					System.out.print("INF     ");
			}
			System.out.println();
		}
	}
	
	//To display the path 
	public static void displayPath(int path[]){
		for(int i=0;i<n;i++){
			System.out.print(path[i]+" ");
		}
		System.out.println();
	}
	
	
	public static void solve(){
		Node current=new Node(n);
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) current.reducedMatrix[i][j]=cost[i][j];
		current.value+=rowReduction(current.reducedMatrix);
		current.value+=columnReduction(current.reducedMatrix);
		current.path[0]=0;
		
		//PriorityQueue to store the nodes based on the values
		PriorityQueue<Node> pq=new PriorityQueue<Node>(new sortByValue());
		pq.add(current);
		
		//stack to handle multiple paths
		Stack<Path> st=new Stack<Path>();

		long leastCost=INF;
		boolean selection[]=new boolean[n];
		
		while(!pq.isEmpty()){
			current=pq.poll();
			
			//Eliminate the node whose value is higher than that of leastCost
			if(current.value > leastCost) continue;
			
			//If it is the last level => exploration of all the nodes is completed
			if(current.level == n-1){
				while(!st.isEmpty() && st.peek().value > current.value) st.pop();
				st.push(new Path(current.path,current.value,n));
				leastCost=current.value;
				continue;
			}

			for(int i=0;i<n;i++) selection[i]=true;
			//selection stores the nodes which have already been explored 
			for(int i=0;i<=current.level;i++) selection[current.path[i]]=false;
			/*
			Uncomment to know the details of the parent node at each stage
			System.out.println("parent node");
			displayPath(current.path);
			displayArr(current.reducedMatrix);
			System.out.println("Parent cost is : "+current.value+"\n");
			*/
			int level=current.level;
			int parent=current.path[level];
			for(int i=0;i<n;i++){
				//Don't visit the node which is already visited or if there is no path from the parent
				if(selection[i] && current.reducedMatrix[parent][i]!=INF){
					Node child=new Node(n);
					child.nodeCpy(current);
					
					//make parent row and ith column INF as they cannot be revisited
					for(int j=0;j<n;j++) child.reducedMatrix[parent][j]=child.reducedMatrix[j][i]=INF;
					
					//Don't visit any node which has already been visited
					for(int j=0;j<=level;j++) child.reducedMatrix[i][current.path[j]]=INF;
						
					child.value+=rowReduction(child.reducedMatrix);
					child.value+=columnReduction(child.reducedMatrix);
					child.path[level+1]=i;
					child.level++;
					child.value+=current.reducedMatrix[parent][i];
					/*
					Uncomment to know the details of child node at each stage
					System.out.println("Child\n");
					displayPath(child.path);
					displayArr(child.reducedMatrix);
					System.out.println("Cost is "+child.value+"\n");
					*/
					pq.add(child);
				}
			}
		}
		System.out.println("Path is/are :");
		while(!st.isEmpty()){
			for(int i=0;i<n;i++) System.out.print(st.peek().path[i]+"->");
			System.out.println(st.peek().path[n]);
			st.pop();
		}
		System.out.println("Minimum cost is "+leastCost);
	}
				
	public static void main(String args[]){
		INF=Integer.MAX_VALUE;
		Scanner ip=new Scanner(System.in);
		System.out.println("Enter the no. of vertices\n");
		n=ip.nextInt();
		cost=new long[n][n];
		System.out.println("Enter the cost matrix\n");
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) {cost[i][j]=ip.nextLong();cost[i][j]=cost[i][j]==0?INF:cost[i][j];}
		solve();
	}
}
