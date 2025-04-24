
#include<stdio.h>
#include<stdlib.h> 
struct Node{
    int value; 
    Node *left; 
    Node *right; 
}; 
Node *root = NULL; 
Node *createNode(int value){
    Node *newNode =(Node*)malloc(sizeof(Node)); 
    newNode->value = value;
    newNode->left = NULL; 
    newNode->right= NULL;
    
    return newNode; 
}
// 
//              4
//      1               7
//  NULL    NULL    NULL        8
        //                  NULL NULL
// 
// 
// 
// 
// 
// 
Node *insert(Node*root, int value){
    if(root == NULL){
        root = createNode(value); 
    }
    if(value != root->value){
        if(value < root->value){
            root->left = insert(root->left, value);  
        } else if( value > root->value){
            root->right = insert(root->right, value); 
        }
    }
    return root; 
}
void preOrder (Node*root){
    if(root!=NULL){
        printf("%d ", root->value); 
        preOrder(root->left); 
        preOrder(root->right);
    }
}
void inOrder (Node*root){
    if(root!=NULL){
        inOrder(root->left); 
        printf("%d ", root->value); 
        inOrder(root->right);
    }
}
void postOrder (Node*root){
    if(root!=NULL){
        postOrder(root->left); 
        postOrder(root->right);
        printf("%d ", root->value); 
    }
}
Node *search (Node*root, int value){
    if(root == NULL){
        return NULL; 
    }
    if(value == root->value){
        return root; 
    } 
    if(value < root->value){
        return search(root->left, value); 
    } 
    
    if(value > root->value){
        return search(root->right, value); 
    }
}
Node* getPredecessor(Node* root) {
    root = root->left;
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}
Node* deleteNode(Node* root, int value) {
    if (root == NULL) {
        puts("Data not found");
        return NULL;
    }
    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    } else if (value == root->value) {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            root = NULL;
        } else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            root = temp;
        } else if (root->right == NULL) {
            Node *temp = root->left; 
            free(root); 
            root = temp; 
        } else {
            Node* temp = getPredecessor(root);
            root->value = temp->value;
            root->left = deleteNode(root->left, temp->value);
        }
    }
    return root;
}
int main(){
    // insert(x): 4 7 1 8
    root = insert(root, 4);
    root = insert(root, 7);
    root = insert(root, 1);
    root = insert(root, 8);
    preOrder(root); 
    puts("");
    inOrder(root);
    puts("");
    
    postOrder(root);
    puts("");
    Node *cari = search(root, 1); 
    if(cari != NULL){
        printf("Correct"); 
    } else {
        printf("NULL"); 
    }
    deleteNode(root, 2);
    puts("");
    deleteNode(root, 7);
    inOrder(root);
    return 0; 
}
