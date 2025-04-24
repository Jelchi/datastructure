#include <stdio.h> 

int arr[100]; 
int index = 1;

// MIN HEAP 
// -----------------------------
// 1. Push ke array 
// 2. Compare with parent
// if < parent, swap & repeat step 2

// MAX HEAP 
// -----------------------------
// 1. Push ke array 
// 2. Compare with parent
// if > parent, swap & repeat step 2

int getParent(int childIndex){
    return  childIndex /2; 
}

int getLeftChild(int parentIndex){
    int child = 2*parentIndex; 
    if(child >= index) return 0; 
    return child;  
}

int getRightChild(int parentIndex){
    int child = (2*parentIndex)+1; 
    if(child >=index) return 0; 
    return child;
}

void swap( int *a, int *b){
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

void insert(int number){
    // push array 
    int indexToCheck = index; 
    arr[index] = number; 
    index++; 

    // compare with parent
    int parent = getParent(indexToCheck); 

    // check: if first data
    while(parent != 0){
        // next step
        // MIN HEAP 

        /*if(arr[indexToCheck] < arr[parent]){
            swap(&arr[indexToCheck], &arr[parent]); 
            indexToCheck = parent;
            parent = getParent(indexToCheck); 
        } else {
            break; 
        }*/

        // Guard pattern
        if(arr[indexToCheck] >= arr[parent]) break; 
        
        swap(&arr[indexToCheck], &arr[parent]); 
        indexToCheck = parent;
        parent = getParent(indexToCheck); 
    }
}

int pop(){
    // Extract Data pertama
    int indexToCheck =1; 
    int returnData = arr[indexToCheck]; 

    // Swap data pertama dan terakhir
    swap(&arr[indexToCheck], &arr[index-1]);
    index--; 

    // compared with child
    while(indexToCheck < index){
        int leftChild = getLeftChild(indexToCheck); 
        int rightChild = getRightChild(indexToCheck); 
        
        int childToSwap = indexToCheck; 
        if(leftChild !=0&&arr[leftChild]<arr[childToSwap]) childToSwap = leftChild; 
        
        if(rightChild !=0 && arr[rightChild] < arr[childToSwap]) childToSwap = rightChild; 

        if(childToSwap == indexToCheck) break; // if no child is smaller, break; 

        swap(&arr[indexToCheck], &arr[childToSwap]);
        indexToCheck = childToSwap; 
    }
    return returnData;
}

void printArr(){
    for(int i=1; i<index; i++){
        printf("%d ", arr[i]); 
    }
    puts(""); 
}

int main(){
    insert(10); 
    insert(21);
    insert(12);  
    insert(23); 
    insert(45); 
    insert(76); 
    insert(25); 
    insert(87); 
    insert(44); 
    printArr(); 

    insert(9); 
    insert(20); 
    insert(7); 
    printArr(); 

    pop();
    pop();
    pop();  
    pop(); 
    insert(3);
    insert(13);  
    printArr(); 

    // pop(); 
    // printArr();  
    return 0; 
}