//recursive binary search 
int rec_bin_search(int* arr,int left,int right,int element){
	int mid=(left+right)/2;
	if(arr[mid] == element)
		return mid;
	if(left == right)
		return -1;
	if(arr[mid] < element)
		return rec_bin_search(arr,mid+1,right,element);
	else
		return rec_bin_search(arr,left,mid,element);
}


//iterative binary search
int iter_bin_srch(int* arr,int size,int element){
	int left=0,right=size-1;
	while(left <= right){
		int mid=(left + right) / 2;
		if(arr[mid] == element)
			return mid;
		if(arr[mid] < element)
			left=mid+1;
		else
			right=mid-1;
	}
	return -1;
}

//recursive linear search
int rec_lin_srch(int* arr,int pos,int size){
	if(pos == size)
		return -1;
	if(arr[pos] == element)
		return pos;
	return rec_lin_srch(arr,pos+1,size);
}

//iterative linear search
int iter_lin_srch(int* arr,int size,int element){
	int i;
	for(i=0;i<size;i++)
		if(arr[i]==element)
			return i;
	return -1;
}
