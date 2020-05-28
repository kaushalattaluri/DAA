#include<stdio.h>
#include<stdlib.h>
#include<string.h>
static int size ;
typedef struct node{
	char ch;
	int freq;
	struct node* left;
	struct node* right;
}node;

node* create(char ch, int freq){
	node* temp = (node *)malloc(sizeof(node));
	temp->ch = ch;
	temp->freq = freq;
	temp->left = temp->right = NULL;
	return temp;
}

void swap(node** a, node** b){
	node* temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(node** arr, int pos){
	int smallest = pos;
	int left = 2*pos+1;
	int right = 2*pos+2;
	if(left < size && arr[left] -> freq < arr[smallest] -> freq) smallest = left;
	if(right < size && arr[right] -> freq < arr[smallest]->freq) smallest = right;
	if(smallest != pos){
		swap(&arr[pos], &arr[smallest]);
		heapify(arr, smallest);
	}
}

void insert(node** arr,node* element){
	arr[size]=element;
	int idx = size ;
	while ( idx > 0 && arr[(idx - 1)/2] -> freq  > element -> freq ){
		arr[idx] = arr[(idx - 1) / 2] ;
		idx = (idx - 1) / 2;
	}
	arr[idx] = element ;
	size++ ;
}

node* extractMin(node** arr){
	swap(&arr[0], &arr[size-1]);
	size--;
	heapify(arr, 0);
	return arr[size];
}

void display_util(int* arr, int n){
	int i;
	for(i = 0 ;i < n ;i++ )
		printf("%d ",arr[i]);
	printf("\n");
}

void decode(node* ele, int* arr, int top){
	if(ele -> left){
		arr[top] = 0;
		decode(ele->left, arr, top+1);
	}
	if(ele -> right){
		arr[top] = 1;
		decode(ele -> right, arr, top+1);
	}
	if(ele->left == NULL){
		printf("Character is %c decoded value is ",ele -> ch);
		display_util(arr, top);
	}
}

void Huffman(node** arr){
	int i;
	for(i = size/2 - 1 ;i >= 0 ;i--) heapify(arr , i);
	while(size > 1){
		node* first_min = extractMin(arr);
		node* second_min = extractMin(arr);
		node* temp = create('$', first_min->freq + second_min->freq);
		temp->left = first_min;
		temp->right = second_min;
		insert(arr, temp);
	}
	int* arr1 = (int* )malloc(sizeof(int)*100);
	int top = 0;
	decode(arr[0], arr1, top);
	free(arr1);
}

int main(){
	printf("Enter the string \n");
	char string[100];int i; int n = 0; size=0;
	scanf("%[^\n]",string);
	int* freq=(int *)calloc(sizeof(int),26);
	for(i = 0 ;i < strlen(string) ;i++ ) if(string[i] != ' ') freq[string[i] - 'a']++;
	for(i = 0 ;i < 26 ;i++ ) if(freq[i]) size++;
	node* array[size];	n = size;	int pos_util=0;
	for(i = 0 ;i < 26 ;i++ ) if(freq[i]) array[pos_util++]=create((char)(i+'a'), freq[i]);
	Huffman(array);
	free(freq);
	for(i = 0 ;i < n ;i++ ) free(array[i]);;
	return 0;
}
