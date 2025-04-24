#include <stdio.h>
#define MAX 5

int parent[MAX];
int rank[MAX]; 

void make_set(int v) {
    parent[v] = v;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b)
        parent[b] = a;
}

void swap(int *a, int*b){
    int temp = *a; 
    *a = *b; 
    *b = temp; 
}

void union_rank(int a, int b) {
    // Combine the two disjoint sets by making the root of a smaller tree to point at 
    // the root node of the larger tree. Small & Big is determined by rank (height) of the node.
    a = find_set(a);
    b = find_set(b);
    if (a != b){
        // If a is smaller than b, we want b to be the parent of a, so swap them.
        if(rank[a] < rank[b])
            swap(&a, &b);
        parent[b] = a;
        // If the rank is same, add the rank for a, because a is the parent.
        if(rank[a] == rank[b])
            rank[a]++;
    }

}

void printParent(){
    for(int i=0;i<MAX;i++){
        printf("%d ", parent[i]);
    }
    printf("\n");
}

void printRank(){
    for(int i=0;i<MAX;i++){
        printf("%d ", rank[i]);
    }
    printf("\n");
}

int main()
{
    for(int i=0;i<MAX;i++){
        make_set(i);
    }
    printParent();
    union_sets(4, 3);
    printParent();
    union_sets(2, 1);
    printParent();
    union_sets(3, 1);
    printParent();
    union_sets(1, 0);
    printParent();

    puts("================"); 
     for(int i=0;i<MAX;i++){
        make_set(i);
    }
    printf("Initial arrays:\n");
    printRank();
    printParent();

    printf("Union(4, 3), rank of 4 added by 1\n");
    union_rank(4, 3);
    printRank();
    printParent();

    printf("Union(2, 1), rank of 2 added by 1\n");
    union_rank(2, 1);
    printRank();
    printParent();

    printf("Union(3, 1), rank of 4 added by 1\n");
    union_rank(3, 1);
    printRank();
    printParent();

    printf("Union(0, 1), because rank of 4 (representative of 1) is higher, swap to Union(1, 0)\n");
    union_rank(0, 1);
    printRank();
    printParent();
    return 0;
}

