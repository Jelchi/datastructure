#include <stdio.h>
#include <stdlib.h>

struct Node{
	int value; 
	int height; 
	Node * right; 
	Node * left; 
};

Node * root = NULL; 

Node * createNode(int value){
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->value = value; 
	newNode->height = 1; 
	newNode->right = NULL; 
	newNode->left = NULL;  
	
	return newNode; 
}

int findMax(int left, int right){
	if(left>right){
		return left; 
	} else {
		return right; 
	}
}

int getHeight(Node * root){
	if(root == NULL){
		return NULL; 
	} else {
		return root->height; 
	}
}

void updateHeight(Node * root){
	root->height = findMax(getHeight(root->left), getHeight(root->right))+1; 
}

int getBalanceFactor(Node * root){
	if(root == NULL){
		return NULL; 
	} else {
		return getHeight(root->left) - getHeight(root->right); 
	}
}

Node * rightRotate(Node*root){
	Node * left = root->left; 
	Node * leftRight = left->right; 
	
	left->right = root; 
	root->left = leftRight; 
	
	updateHeight(root); 
	updateHeight(left); 
	
	return left; 
}

Node * leftRotate(Node*root){ // 21
	Node * right = root->right; // 26
	Node * rightLeft = right->left; 
	
	right->left = root; 
	root->right = rightLeft; 
	
	updateHeight(root); 
	updateHeight(right); 
	
	return right; 
}

Node * balancing (Node * root){
	updateHeight(root); 
	int bf = getBalanceFactor(root); 
	
	if(bf>1){
		if(getBalanceFactor(root->left)>0){
			//LL rotation
			root = rightRotate(root); 
		} else {
			//LR rotation
			root->left = leftRotate(root->left); 
			root = rightRotate(root); 
		}
	} else if(bf <-1){
		if(getBalanceFactor(root->right)<0){
			//RR rotation		
			root = leftRotate(root); 
		} else {
			//RL rotation
			root->right = rightRotate(root->right); 
			root = leftRotate(root); 
		}
	}
	return root; 
}

Node * insertion(Node * root, int value){
	 if(root == NULL){
	 	return createNode(value); 
	 } 
	 if (value != root->value){
		 if(value < root->value){
		 	root->left = insertion (root->left, value); 
		 } else if(value > root->value){
		 	root->right = insertion (root->right, value); 
		 } else {
		 	return root; 
		 }
	 }	 
	 return balancing (root); 
}

Node *insertData(Node *root){
	int value; 

	printf("Insert: "); 
	scanf("%d", &value); 
	getchar(); 
	
	root = insertion(root, value); 
	return root;
}

Node * searching(Node * root, int value){
	if(root == NULL){
		return NULL; 
	} 
	
	if(value == root->value){
		return root; 
	} 
	
	if(value < root->value){
		return searching(root->left,value); 
	} 
	
	if(value > root->value){
		return searching(root->right, value); 
	}	
}

Node * getPredecessor(Node * root){
	root = root->left; 
	
	while (root->right != NULL){
		root = root->right; 
	}
	return root; 
}

Node * deletion(Node * root, int value){
	if(root == NULL){
		return NULL; 
	}
	
	if(value < root->value){
		root->left = deletion(root->left, value); 
	} else if(value > root->value){
		root->right = deletion(root->right, value); 
	} else if(value == root->value){
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL; 
		} else if(root->left == NULL){
			 Node * temp = root->right; 
			 free(root); 
			 root = temp; 
		} else if(root->right == NULL){
			Node * temp = root->left; 
			free(root); 
			root = temp; 
		} else {
			Node * temp = getPredecessor(root); 
			root->value = temp->value; 
			root->left =  deletion(root->left, temp->value); // delete the predecessor root
		}
		return root; 
	}
	return balancing(root); 
}

void deleteData(){
	int valueToSearch; 
	printf("Delete: "); 
	scanf("%d", &valueToSearch); 
	getchar(); 
	
	Node * result = searching(root, valueToSearch);
	
	if(result == NULL){
		puts("Data not found");
	} else {
		puts("Data Found"); 
		root = deletion(root, result->value); 
		printf("Value %d was delete\n", valueToSearch); 
	}
}


void inOrder(Node*root){
	if(root != NULL){
		inOrder(root->left); 
		printf("%d ", root->value); 
		inOrder(root->right); 
	}
}

void preOrder(Node*root){
	if(root != NULL){
		printf("%d ", root->value);
		preOrder(root->left);
		preOrder(root->right);  
	}
}

void postOrder(Node*root){
	if(root != NULL){
		postOrder(root->left); 
		postOrder(root->right); 
		printf("%d ", root->value); 
	}
}

void mainMenu(){
	int opt; 
	do {
		puts("1. Insertion");
		puts("2. Deletion"); 
		puts("3. Traversal");
		puts("4. Exit"); 
		printf("Choose: ");  
		scanf("%d", &opt); 
		getchar(); 
		
		system("cls"); 
		switch(opt){
			case 1: 
				root = insertData(root); 
				break; 
				
			case 2: 
				deleteData(); 
				system("pause"); 
				break; 
				
			case 3: 
					if(root == NULL){
						puts("Data Empty"); 
						system("pause");
						break ;
					}
					puts("Notation: "); 
	
					printf("In-order Notation: "); 
					inOrder(root); 
					puts(""); 
					
					printf("Pre-order Notation: "); 
					preOrder(root); 
					puts(""); 
					
					printf("Post-order Notation: "); 
					postOrder(root); 
					puts(""); 
				system("pause"); 
				break; 
				
			case 4: 
				puts("Thank You"); 
				system("pause"); 
				break;
				
			default: 
				puts("Invalid Input");
				system("pause"); 
				break; 
		}
		system("cls"); 
	}while(opt!=4); 
}

int main(){
	mainMenu(); 
	return 0; 
}
