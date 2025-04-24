#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	char name[101]; 
	char email[101]; 
	char id[101]; 
	char gender[101];
	int age; 
	
	int height; 
	Node * left; 
	Node * right; 
};

Node * root = NULL; 

Node * createNode(char *name, char * email, char*id, int age, char *gender){
	Node * newNode = (Node *)malloc(sizeof(Node)); 
	strcpy(newNode->name, name); 
	strcpy(newNode->email, email); 
	strcpy(newNode->id, id); 
	newNode->age = age; 
	strcpy(newNode->gender, gender); 
	
	newNode->height = 1; 
	newNode->left = NULL; 
	newNode->right = NULL; 
	
	return newNode;
}

char * getId(char *gender){
	char id [101];
	int a = rand() %10;
	int b = rand() %10;
	int c = rand() %10; 
	
	if(strcmp(gender, "Male") == 0){
		sprintf(id, "M%d%d%d", a, b,c); 
	} else if (strcmp(gender, "Female") == 0){
		sprintf(id, "F%d%d%d", a,b, c); 
	}
	return id; 
}

int findMax(int a, int b){
	if(a<b){
		return b; 
	} 
	return a; 
}

int getHeight(Node*root){
	if(root == NULL){
		return NULL; 
	}
	return root->height;
}

void updateHeight(Node *root){
	root->height = findMax(getHeight(root->left), getHeight(root->right))+1; 
}

int getBalancingFactor(Node*root){
	if(root==NULL){
		return NULL; 
	} 
	return getHeight(root->left) - getHeight(root->right);
}

Node* rightRotate(Node *root){
	Node * left = root->left; 
	Node * leftRight = left->right; 
	
	left->right = root; 
	root->left =  leftRight; 
	
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

Node * balancing(Node*root){
	updateHeight(root); 
	int bf = getBalancingFactor(root); 
	
	if(bf > 1){
		if(getBalancingFactor(root->left) >=0){
			//LL Rotation
			root = rightRotate(root); 
		} else {
			// LR Rotation
			root->left =  leftRotate(root->left); 
			root = rightRotate(root); 
		}
	} else if(bf < -1){
		if(getBalancingFactor(root->right) <=0){
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

Node * insertNode(Node *curr, Node * newNode){
	if(curr == NULL) return newNode;
	
	if(strcmp(curr->id, newNode->id) > 0){
		curr->left = insertNode(curr->left, newNode); 
	} else if(strcmp(curr->id, newNode->id) <0){
		curr->right = insertNode(curr->right, newNode); 
	}
	
	return balancing(curr); 
}

Node * searchName(Node * root, char *name){
	if(root == NULL || strcmp(root->name, name) == 0){
		return root; 
	}
	if(strcmp(root->name, name) > 0){
		root->left = searchName(root->left, name); 
	} else if (strcmp(root->name, name) < 0){
		root->right = searchName(root->right, name); 
	} 
}

bool checkingEmail(char * email){
	int len = strlen(email); 
	int at = 0; 
	int dot = 0;
	
	for(int i=0; i<len; i++){
		if(email[i] == '@'){
			at = i; 
		}
		
		if(email[i] == '.'){
			dot = i; 
		}
	} 
	
	if(strncmp(email+dot, ".com", 4) != 0){
		return false; 
	}
	
	if(at != 0 && at < dot-1 && dot == len-4){
		return true; 
	}
	return false; 
}

void insertData(){
	char name[101]; 
	char email[101]; 
	char gender[101]; 
	int age; 
	
	char temp[101]; 
	int word; 
	do{
		word = 0; 
		printf("Name: "); 
		scanf("%[^\n]", &name); 
		getchar();
		
		strcpy(temp, name); 
		char * token = strtok(temp, " "); 
		while (token != NULL){
			word++; 
			token = strtok(NULL, " "); 
		} 
	}while(word != 2 || searchName(root, name) != 0);
	
	do{
		printf("Email: "); 
		scanf("%[^\n]", &email); 
		getchar(); 
	} while(!checkingEmail(email));
	
	do{
		printf("Gender: "); 
		scanf("%s", &gender); 
		getchar(); 
	} while (strcmp(gender,"Male")!=0 && strcmp(gender, "Female") !=0); 
	
	do{
		printf("Age: "); 
		scanf("%d", &age); 
		getchar(); 
	} while(age < 1); 
	
	char id[101]; 
	strcpy(id, getId(gender)); 
	
	root = insertNode(root, createNode(name, email, id, age, gender)); 
	puts("Successfully");
}

void inorder(Node*root){
	if(root== NULL){
		return; 
	}
	inorder(root->left); 
	printf("Name: %s\nEmail: %s\nID: %s\nAge: %d\nGender: %s\n", root->name, root->email, root->id, root->age, root->gender); 
	inorder(root->right); 
}

void displayNode(){
	if(root == NULL){
		puts("Data doesn't exist"); 
		return; 
	} else {
		inorder(root); 
	}
}

Node * deletion(Node * curr, char *id){
	if(curr == NULL){
		return NULL; 
	}
	
	if(strcmp(curr->id, id) >0){
		curr->left = deletion(curr->left, id); 
	} else if(strcmp(curr->id, id) <0){
		curr->right = deletion(curr->right, id); 
	} else {
		if(curr->left == NULL && curr->right == NULL){
			free(curr); 
			return NULL; 
		} else if(curr->right == NULL && curr->left != NULL){
			Node * temp = curr; 
			curr = curr->left; 
			free(temp); 
		} else if(curr->right != NULL && curr->left == NULL){
			Node *temp = curr; 
			curr = curr->right; 
			free(temp); 
		} else {
			Node * successor = curr->right; 
			while(curr->left != NULL){
				curr = curr->left; 
			} 
			strcpy(curr->name, successor->name); 
			strcpy(curr->email, successor->email); 
			strcpy(curr->id, successor->id); 
			strcpy(curr->gender, successor->gender); 
			curr->age = successor->age; 
			
			curr->right = deletion(curr->right, successor->id); 
		}
	}
	return balancing(curr); 
}

void pop(){
	displayNode(); 
	
	char id1[10]; 
	printf("Input id: ");
	scanf("%[^\n]", id1); 
	getchar(); 
	
	root =deletion(root, id1);  
}

Node * searchId(Node * root, char * id){
	if(root == NULL ){
		return NULL; 
	} else if(strcmp(root->id , id) >0){
		root->left = searchId(root->left, id); 
	} else if(strcmp(root->id, id) <0){
		root->right = searchId(root->right, id); 
	} else {
		return root ; 
	}
}

void update(){
	if(root == NULL){
		puts("Data Empty"); 
		return; 
	}
	inorder(root);  
	
	char id2[10]; 
	printf("Input id: ");
	scanf("%[^\n]", id2); 
	getchar(); 
	
	Node * r =  searchId(root , id2); 
	if(r != NULL){
		printf("Data doesn't exist"\n); 
	} else {
		char name1[101]; 
		char temp1[101]; 
		printf("Name: "); 
		scanf("%[^\n]", &name1); 
		getchar();
		
		strcpy(r->name, name1); 
		
	}
}

void mainMenu(){
	int opt; 
	do {
		puts("1. Insert"); 
		puts("2. View"); 
		puts("3. Update"); 
		puts("4. Delete"); 
		puts("5. Exit"); 
		printf(">> "); 
		scanf("%d", &opt); 
		getchar(); 
		
		switch(opt){
			case 1:
				insertData(); 
				break; 
				
			case 2: 
				displayNode(); 
				break; 
				
			case 3: 
				update(); 
				break; 
				
			case 4: 
				pop(); 
				break; 
				
			case 5: 
				puts("terimakasih"); 
				break; 
				
			default: 
				puts("Invalid Input"); 
				break; 
		}
	}while(opt !=5); 
}

int main(){
	mainMenu(); 
	return 0; 
}
