#include <stdio.h>
#include <stdlib.h>

struct Node{
	int value; 
	Node * left; 
	Node * right; 
	int height; 
};

Node * root = NULL;  

Node * createNode (int value){
	Node * newNode = (Node *)malloc(sizeof(Node)); 
	newNode->value = value; 
	newNode->height = 1; 
	newNode->left = NULL; 
	newNode->right = NULL; 
	
	return newNode; 
}

int findMax(int a, int b){
	if (a<b){
		return b; 
	}
	return a;
}

int getHeight(Node * root){
	if(root== NULL){
		return NULL; 
	} 
	return root->height; 
}

void updateHeight(Node * root){
	root->height = findMax(getHeight(root->left), getHeight(root->right))+1; 
}

int getBalanceFactor(Node * root){
	if(root==NULL){
		return NULL; 
	} 
	return getHeight(root->left) - getHeight(root->right); 
}

Node * rightRotate(Node * root){
	Node * left = root->left; 
	Node * leftRight = left->right; 
	
	left->right = root; 
	root->left = leftRight; 
	
	updateHeight(root); 
	updateHeight(left); 
	
	return left; 
}

Node * leftRotate(Node * root){
	Node * right = root->right; 
	Node * rightLeft = right->left; 
	
	right->left = root; 
	root->right = rightLeft; 
	
	updateHeight(root); 
	updateHeight(right); 
	
	return right; 
}

Node * balancing(Node * root){
	updateHeight(root); 
	int bf = getBalanceFactor(root);
	
	if(bf > 1){
		if(getBalanceFactor(root->left) >=0){
			root = rightRotate(root); 
		} else {
			root->left = leftRotate(root->left); 
			root = rightRotate(root); 
		}
	} else if (bf < -1){
		if(getBalanceFactor(root->right) <=0){
			root = leftRotate(root); 
		} else {
			root->right = rightRotate(root->right); 
			root = leftRotate(root); 
		}
	}
	return root; 
}

Node * push(Node*root, Node*newNode){
	if(root == NULL) return newNode; 
	
	if(root->value > newNode->value){
		root->left = push(root->left , newNode); 
	} else if(root->value < newNode->value){
		root->right = push(root->right, newNode); 
	} 
	return balancing(root); 
}

void inOrder(Node * root){
	if(root == NULL){
		return; 
	} else {
		inOrder(root->left); 
		printf("%d ", root->value); 
		inOrder(root->right); 
	}
}

void display(){
	if(root== NULL){
		puts("Data Kosong"); 
		return; 
	}
	inOrder(root); 
}

Node * searching(Node *root, int value){
	if(root == NULL){
		return NULL; 
	}
	if(root->value > value){
		return root->left = searching(root->left, value ); 
	} else if(root->value < value){
		return root->right = searching(root->right,value); 
	} else if(root->value == value){
		return root; 
	}
}

Node * deleteNode(Node * root, int value){
	if(root== NULL){
		return NULL; 
	} 
	if(root->value > value){
		root ->left = deleteNode(root->left, value); 
	} else if(root->value < value){
		root->right = deleteNode(root->right, value); 
	} else {
		if(root->right == NULL && root->left == NULL){
			free(root); 
			return NULL; 
		} else if(root->right == NULL && root->left != NULL){
			Node * temp = root; 
			root = root->left; 
			free(temp); 
		} else if(root->right != NULL && root->left == NULL){
			Node *temp = root; 
			root = root->right; 
			free(temp); 
		} else {
			Node * succ = root->right; 
			while(root->left !=  NULL){
				root = root->left; 
			} 
			root->value = succ->value; 
			root->right  = deleteNode(root->right, succ->value); 
		}
	}
}

int main (){
	root = push(root, createNode(1)); 
	root = push(root, createNode(3)); 
	root = push(root, createNode(2)); 
	root = push(root, createNode(5)); 
	root = push(root, createNode(7)); 
	display(); 
	
	Node * r = searching(root, 7); 
	if(r == NULL){
		puts("Tidak ketemu"); 
	}
	printf("\n%d\n ", r->value);  
	
	deleteNode(root, r->value); 
	display(); 
	return 0; 
}
