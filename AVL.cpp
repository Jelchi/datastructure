#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    Node *left;
    Node *right;
    int height;
};

Node *root = NULL;

Node* createNode(int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->right = newNode->left = NULL;
    newNode->height = 1;
    
    return newNode;
}

int max(int a, int b) {
    if(a > b) {
        return a;
    }
    return b;
}

int getHeight(Node *p) {
    if(!p) {
        return 0;
    }
    return p->height;
}

int getBF(Node *p) {
    if(!p) {
        return 0;
    }
    return getHeight(p->left) - getHeight(p->right);
}

Node *rightRotate(Node *A) {
    Node *b = A->left;
    Node *c = b->right;
    b->right = A;
    A->left = c;

    A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;

    return b;
}

Node *leftRotate(Node *A) {
    Node *b = A->right;
    Node *c = b->left;
    b->left = A;
    A->right = c;

    A->height = max(getHeight(A->left), getHeight(A->right)) + 1;
    b->height = max(getHeight(b->left), getHeight(b->right)) + 1;

    return b; 
}

Node* insert(Node *curr, int value) {
    if(curr == NULL) {
        return createNode(value);
    } else if(value < curr->value) {
        curr->left = insert(curr->left, value);
    } else if(value > curr->value) {
        curr->right = insert(curr->right, value);
    }
    curr->height = max(getHeight(curr->left), getHeight(curr->right)) + 1;

    int bf = getBF(curr);

    if(bf > 1) {
        if(getBF(curr->left) > 0) {
            // RR Rotation
            curr = rightRotate(curr);
        } else {
            // LR Rotation
            curr->left = leftRotate(curr->left);
            curr = rightRotate(curr);
        }
    } else if(bf < -1) {
        if(getBF(curr->right) < 0) {
            // LL Rotation
            curr = leftRotate(curr);
        } else {
            // RL Rotation
            curr->right = rightRotate(curr->right);
            curr = leftRotate(curr);
        }
    }


    return curr;
}

void preOrder(Node *root) {
    if(root) {
        printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
    return;
}


void inOrder(Node *root) {
    if(root) {
        inOrder(root->left);
        printf("%d ", root->value);
        inOrder(root->right);
    }
    return;
}


void postOrder(Node *root) {
    if(root) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->value);
    }
    return;
}

int main() {
    root = insert(root, 5);
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 3);
    inOrder(root);
    return 0;
}
