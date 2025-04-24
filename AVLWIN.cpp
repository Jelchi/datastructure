#include <stdio.h> 
#include <stdlib.h> 

struct Node{
    int value; 
    Node * left , *right;
    int height;  
}; 

Node * root = NULL; 

Node * createNode(int value){
    Node * newNode = (Node*)malloc(sizeof(Node)); 
    newNode->value = value; 
    newNode->left = NULL; 
    newNode->right = NULL;

    return newNode; 
}

Node *push(Node * current, Node*newNode){
    if(current == NULL){
        return newNode; 
    }  else if(newNode->value == current->value){
        printf("Must be unique"); 
    } else if(current->value > newNode->value){
        current->left =push(current->left, newNode); 
    } else if( newNode->value >= current->value){
        current->right = push(current->right, newNode); 
    }

    return current; 
}

// Node * pop(int value){
// }

void print(Node *root){
    if(root != NULL){
        printf("%d", root->value); 
        print(root->left); 
        print(root->right); 
    }
}

int main(){
    root = push(root, createNode(1));
    print(root); 
    return 0; 
}