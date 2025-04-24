#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
	char symbols[101]; 
	double price; 
	int volume; 
	int key; 
		
	int height; 
	Node * left; 
	Node * right; 
};

Node * root = NULL; 

Node * createNode(char*symbols, double price, int volume, int key){
	Node * newNode = (Node*)malloc(sizeof(Node)); 
	strcpy(newNode->symbols, symbols); 
	newNode->price = price; 
	newNode->volume = volume; 
	newNode->key = key; 
	newNode->height = 1; 
	
	newNode->left = NULL; 
	newNode->right = NULL; 
	return newNode; 
}

int getKey(char *symbols){
	int result = 0; 

	for(int i=0; i<strlen(symbols); i++){
        result += symbols[i]; 
    }
    return result; 
}

int findMax(int a, int b){
	if(a<b){
		return b; 
	} 
	return a; 
}

int getHeight(Node* root){
	if(root == NULL){
		return 0; 
	}
	return root->height; 
}

void updateHeight(Node * root){
	root->height = findMax(getHeight(root->left), getHeight(root->right))+1; 
}

int getBalanceFactor(Node *root){
	return getHeight(root->left) - getHeight(root->right); 
}

Node * rightRotate(Node * root){
	Node * left = root->left; 
	Node *leftRight = left->right; 
	
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


Node * balancing(Node* root){
	updateHeight(root); 
	int bf = getBalanceFactor(root); 
	
	if(bf > 1){
		if(getBalanceFactor(root->left) > 0){
			// LL Rotation
			root = rightRotate(root); 
		} else {
			// LR Rotation
			root->left = leftRotate(root->left); 
			root = rightRotate(root); 
		}
	} else if(bf < -1){
		if(getBalanceFactor(root->right) <0){
			// RR Rotation
			root = leftRotate(root);
		} else {
			// RL Rotation
			root->right = rightRotate(root->right);
			root = leftRotate(root); 
		}
	}
	return root; 
}

Node * push(Node * curr, Node * newNode){
	if(!curr) return newNode; 
	
	if(curr->key > newNode->key) {
		curr->right = push(curr->right, newNode); 
	} else if(curr->key < newNode->key) {
		curr->left = push(curr->left, newNode);
	} else if(curr->key == newNode->key){
		return NULL; 
	}
	return balancing(curr); 
}

void addStock(){
	char symbols[101]; 
	double price; 
	int volume; 
	
	printf("Enter Stock symbols: "); 
	scanf("%[^\n]", &symbols); 
	getchar(); 
	
	printf("Enter Stock price: ");
	scanf("%lf", &price); 
	getchar(); 
	
	printf("Enter stock volume: "); 
	scanf("%d", &volume); 
	getchar(); 
	
	int key;
	key = getKey(symbols); 
	 
	root = push(root, createNode(symbols, price, volume, key)); 
	printf("Success! Stock Key (index): %d\n", key); 	
}

Node * searching(Node * root, int key){
	if (root == NULL || root->key == key) {
        return root;
    }

    if (root->key < key) {
        return searching(root->right, key);
    }

    return searching(root->left, key);
}

Node * updatePrice(Node * root){
	int key;
	double price; 
	
	printf("Enter key to update: ");
    scanf("%d", &key);
    getchar(); 
    
	Node * result  = searching(root, key); 
	if(result == NULL){
		puts("Not founded"); 
	} else {
		printf("Enter new stock price: ");
        scanf("%lf", &price);
        getchar(); 
		result->price = price; 
	}
}

Node * pop (Node * curr, int key){
	if(curr == NULL){
		return NULL; 
	} else if(curr->key > key){
		curr->left = pop(root->left, key);
	} else if(curr->key <key){
		curr->right = pop(root->right, key); 
	} else {
		if(curr->left == NULL && curr->right == NULL){
			free(curr); 
			return NULL; 
		} else if(curr->left == NULL && curr->right != NULL){
			Node * temp = curr->right;
			free(curr); 
			curr = temp; 
		} else if(curr->right == NULL && curr->left != NULL){
			Node * temp = curr->left; 
			free(curr); 
			curr = temp; 
		} else {
			Node * temp = curr->right;
			while(temp->left){
				temp = temp->left;
			}

			strcpy(curr->symbols, temp->symbols);
            curr->price = temp->price;
            curr->volume = temp->volume;
            curr->key = temp->key;
            curr->right = pop(curr->right, temp->key);
		}
	}
	return balancing(curr);
}

void deleteStock(){
	int key; 
	printf("Enter key to delete: ");
    scanf("%d", &key);
    root = pop(root, key);
}

void display(Node*root){
	if(root){	
		display(root->left); 
		printf("Key: %d | Symbols: %s,  price: %0.2f, volume: %d\n", 
		root->key, root->symbols, root->price, root->volume); 
		display(root->right); 
	}
}

void mainMenu(){
	int opt; 
	
	do{
		puts("Stock Market Analysis System"); 
		puts("1. Add Stock"); 
		puts("2. List Stocks"); 
		puts("3. Update Stock price"); 
		puts("4. Delete Stock"); 
		puts("5. Exit"); 
		printf("Enter Your Choice: "); 
		
		scanf("%d", &opt); 
		getchar(); 
		
		switch(opt){
			case 1: 
				addStock(); 
				break; 
			
			case 2:
				display(root); 
				break; 
				
			case 3:
				updatePrice(root); 
				break; 
				
			case 4: 
				deleteStock(); 
				display(root); 
				break; 
				
			case 5:
				puts("Thank You"); 
				break; 
				
			default: 
				puts("Invalid Input");
				break; 
		}
	} while(opt!=5); 
}

int main(){
	mainMenu();  
	return 0; 
}
