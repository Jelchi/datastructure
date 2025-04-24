#include <stdio.h>
#include <limits.h> //INT_MAX INT_MIN 

int parent(int pos){
	return (pos-1)/2; 
}

int leftChild(int pos){
	return (pos*2)+1; 
}

int rightChild(int pos){
	return (pos*2)+2; 
}

int heap[100] = {INT_MAX}; 
int size; 

void swap(int * a, int * b){
	int temp = *a;
	*a = *b; 
	*b = temp; 
}

void insertHeap(int value){
	heap[size] = value; 
	int pos = size;
	size++;
	
	while(heap[parent(pos)]> heap[pos]){
		printf("Swapping %d with %d\n", heap[parent(pos)], heap[pos]); 
		swap(&heap[pos], &heap[parent(pos)]); 
		pos = parent(pos); 
	}
	printf("Successfully insert %d\n", value); 
}

void printArray(){
	for(int i =0; i< size;i++){
		printf("%d ", heap[i]); 
	} 
	puts(""); 
}

void heapify(int pos){
	int left, right; 
	if(leftChild(pos)>size){
		left = INT_MAX; 
	} else {
		left = heap[leftChild(pos)]; 
	}
	
	if(rightChild(pos)>size){
		right = INT_MAX; 
	} else {
		right = heap[rightChild(pos)]; 
	}
	
	if(heap[pos] > right || heap[pos]> left){
		puts("Swapp"); 
		
		if(left < right){
			swap(&heap[pos], &heap[leftChild(pos)]); 
			heapify(leftChild(pos)); 
		} else {
			swap(&heap[pos], &heap[rightChild(pos)]); 
			heapify(rightChild(pos)); 
		}
	}
}

int extractMin(){
	if(size == 0){
		printf("Heap is empty"); 
		return 0; 
	}
	int minValue = heap[0]; 
	
	heap[0] = heap[size-1]; 
	size--; 
	
	heapify(0); 
	return minValue;
}

int main(){
	insertHeap(10); 
	insertHeap(1); 
	insertHeap(12); 
	insertHeap(17); 
	insertHeap(3); 
	printArray(); 
	
	while(true){
		printf("Extracting------- %d\n", extractMin()); 
		if(size == 0){
			break; 
		}
	}
	return 0; 
}
