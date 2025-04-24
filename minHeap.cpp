#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

// Structure to represent a min heap
struct MinHeap {
    int *arr; // Array to store heap elements
    int capacity; // Maximum capacity of the heap
    int size; // Current size of the heap
};

// Function to create a new min heap
struct MinHeap *createMinHeap(int capacity) {
    struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));
    minHeap->arr = (int *)malloc(capacity * sizeof(int));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    return minHeap;
}

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain min heap property
void heapify(struct MinHeap *minHeap, int index) {
    int smallest = index; // Initialize smallest as root
    int left = 2 * index + 1; // Left child index
    int right = 2 * index + 2; // Right child index

    // Compare with left child
    if (left < minHeap->size && minHeap->arr[left] < minHeap->arr[smallest]) {
        smallest = left;
    }

    // Compare with right child
    if (right < minHeap->size && minHeap->arr[right] < minHeap->arr[smallest]) {
        smallest = right;
    }

    // If smallest is not root
    if (smallest != index) {
        swap(&minHeap->arr[index], &minHeap->arr[smallest]);
        heapify(minHeap, smallest); // Recursively heapify the affected subtree
    }
}

// Function to insert a new element into the min heap
void insert(struct MinHeap *minHeap, int value) {
    if (minHeap->size == minHeap->capacity) {
        printf("Error: Heap overflow\n");
        return;
    }

    // Insert the new element at the end
    int index = minHeap->size;
    minHeap->arr[index] = value;
    minHeap->size++;

    // Heapify the element upwards to maintain heap property
    while (index != 0 && minHeap->arr[(index - 1) / 2] > minHeap->arr[index]) {
        swap(&minHeap->arr[index], &minHeap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Function to delete the minimum element from the min heap
void deleteMin(struct MinHeap *minHeap) {
    if (minHeap->size == 0) {
        printf("Error: Heap is empty\n");
        return;
    }

    // Replace the root with the last element
    minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
    minHeap->size--;

    // Heapify the root downwards to maintain heap property
    heapify(minHeap, 0);
}

// Function to print the elements of the min heap
void printHeap(struct MinHeap *minHeap) {
    printf("Min Heap: ");
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->arr[i]);
    }
    printf("\n");
}

int main() {
    struct MinHeap *minHeap = createMinHeap(MAX_HEAP_SIZE);

    insert(minHeap, 10);
    insert(minHeap, 21);
    insert(minHeap, 23);
    insert(minHeap, 45);
    insert(minHeap, 76);
    insert(minHeap, 25); 
    insert(minHeap, 87);
    insert(minHeap, 44);  
    printHeap(minHeap); // Output: Min Heap: 5 15 10 20 30


    deleteMin(minHeap);

    printHeap(minHeap); // Output: Min Heap: 10 15 30 20

    return 0;
}
