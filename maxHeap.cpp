#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

// Structure to represent a max heap
struct MaxHeap {
    int *arr; // Array to store heap elements
    int capacity; // Maximum capacity of the heap
    int size; // Current size of the heap
};

// Function to create a new max heap
struct MaxHeap *createMaxHeap(int capacity) {
    struct MaxHeap *maxHeap = (struct MaxHeap *)malloc(sizeof(struct MaxHeap));
    maxHeap->arr = (int *)malloc(capacity * sizeof(int));
    maxHeap->capacity = capacity;
    maxHeap->size = 0;
    return maxHeap;
}

// Function to swap two integers
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function to maintain max heap property
void heapify(struct MaxHeap *maxHeap, int index) {
    int largest = index; // Initialize largest as root
    int left = 2 * index + 1; // Left child index
    int right = 2 * index + 2; // Right child index

    // Compare with left child
    if (left < maxHeap->size && maxHeap->arr[left] > maxHeap->arr[largest]) {
        largest = left;
    }

    // Compare with right child
    if (right < maxHeap->size && maxHeap->arr[right] > maxHeap->arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != index) {
        swap(&maxHeap->arr[index], &maxHeap->arr[largest]);
        heapify(maxHeap, largest); // Recursively heapify the affected subtree
    }
}

// Function to insert a new element into the max heap
void insert(struct MaxHeap *maxHeap, int value) {
    if (maxHeap->size == maxHeap->capacity) {
        printf("Error: Heap overflow\n");
        return;
    }

    // Insert the new element at the end
    int index = maxHeap->size;
    maxHeap->arr[index] = value;
    maxHeap->size++;

    // Heapify the element upwards to maintain heap property
    while (index != 0 && maxHeap->arr[(index - 1) / 2] < maxHeap->arr[index]) {
        swap(&maxHeap->arr[index], &maxHeap->arr[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

// Function to delete the maximum element from the max heap
void deleteMax(struct MaxHeap *maxHeap) {
    if (maxHeap->size == 0) {
        printf("Error: Heap is empty\n");
        return;
    }

    // Replace the root with the last element
    maxHeap->arr[0] = maxHeap->arr[maxHeap->size - 1];
    maxHeap->size--;

    // Heapify the root downwards to maintain heap property
    heapify(maxHeap, 0);
}

// Function to print the elements of the max heap
void printHeap(struct MaxHeap *maxHeap) {
    printf("Max Heap: ");
    for (int i = 0; i < maxHeap->size; i++) {
        printf("%d ", maxHeap->arr[i]);
    }
    printf("\n");
}

int main() {
    struct MaxHeap *maxHeap = createMaxHeap(MAX_HEAP_SIZE);

    // 45, 36, 54, 27, 63, 72, 61, and 18
    insert(maxHeap, 45);
    insert(maxHeap, 36);
    insert(maxHeap, 54);
    insert(maxHeap, 27);
    insert(maxHeap, 63);
    insert(maxHeap, 72); 
    insert(maxHeap, 61); 
    insert(maxHeap, 18);
    
    printHeap(maxHeap); // Output: Max Heap: 30 20 5 10 15

    deleteMax(maxHeap);

    printHeap(maxHeap); // Output: Max Heap: 20 15 5 10

    return 0;
}
