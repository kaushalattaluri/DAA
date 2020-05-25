#include<stdio.h>
#include<stdlib.h>

void swap(int* a,int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void merge(int arr[], int left , int right){
	//creating an array of size right-left+1
	int temp[right-left+1];
	int mid = (left + right) / 2;
	int i=left , j=mid+1 , c=0;
	//divide the array into two equal parts and start placing the elements 
	//by comparing arr[i] and arr[j]
	while(i <= mid && j <= right){
		if( arr[i] < arr[j]) temp[c++] = arr[i++];
		else temp[c++] = arr[j++];
	}

	//these to conditions will make sure that remaning elements of left and right arrays are
	//placed into temp array
	while(i <= mid ) temp[c++] = arr[i++];
	while(j <= right) temp[c++] = arr[j++];
	
	//here we insert the elements back to our original array
	for(c = 0 ; c < (right - left + 1) ; c++ ) arr[left+c] = temp[c];
}

void merge_sort(int arr[], int left, int right){
	if(left < right ){
		//this condition makes sure that there are atleast two elements in consideration
		int mid=(left + right )/2;
		merge_sort(arr , left , mid);
		merge_sort(arr , mid + 1 , right);
		merge(arr, left , right);
	}
}
int partition(int arr[], int left, int right){
	int i = left-1,j;
	//ith position indicates that elements to the left of i are less than or equal to arr[right]
	//and to the right are greater than arr[right]
	//so everytime we encounter the condition that arr[j] is less than or equal to arr[right],
	//we increment the i value and we swap arr[i] & arr[j]
	//the reason for swapping is to bring the elements less than i to its left
	for(j = left ; j < right ; j++){

		if(arr[j] <= arr[right]){
			++i;
			swap(&arr[i],&arr[j]);
		}
	}
	//this swapping is to insert arr[right] in its correct position
	swap(&arr[i+1],&arr[right]);

	//we return i+1 to indicate that we now placed arr[right] in its right position
	//and now we are concerned to sort arr[l...i] and arr[i+2 .... r]
	return i+1;
}
			
void quick_sort(int arr[],int left, int right){
	if(left < right){
		//this condition makes sure that there are atleast two elements in consideration
		int pivot=partition(arr,left,right);
		//element pivot is inserted at the position that of what we can find it in a sorted array
		//put in simple words, pivot position element is in it's right place
		

		//To sort the left array
		quick_sort(arr,left,pivot-1);
		//and right array
		quick_sort(arr,pivot+1,right);
	}
}
int main(){
	int n, i, choice;
	printf("Enter the no. of elements\n");
	scanf("%d",&n);
	int arr[n];

	printf("Enter the elements\n");
	for(i = 0 ; i < n; i++ ) scanf("%d",&arr[i]);

	printf("Enter 1.Quick sort 2.Merge sort\n");
	scanf("%d",&choice);

	if(choice == 1) quick_sort(arr,0,n-1);
	else if(choice == 2) merge_sort(arr,0,n-1);
	else printf("Wrong choice\n");

	if(choice == 1 || choice == 2){
		printf("The sorted array is\n");
		for( i = 0 ;i < n ; i++) printf("%d ",arr[i]);
	}

	return 0;
}
