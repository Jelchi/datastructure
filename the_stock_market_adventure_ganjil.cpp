#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
	char stock [101]; 
	char id[101];
	int portofolio; 
	double price; 
	int volume; 
	int height; 

	Node * left; 
	Node * right; 
};

Node * root = NULL; 

Node * createNode(char *stock, char * id, int portofolio, double price, int volume){
	Node * newNode = (Node*)malloc(sizeof(Node)); 
	strcpy(newNode->stock, stock); 
	strcpy(newNode->id, id); 
	newNode->portofolio = portofolio; 
	newNode->price = price;
	newNode->volume = volume;
	
	newNode->height = 1; 
	newNode->left = NULL; 
	newNode->right = NULL; 
	
	return newNode; 
}

bool isUpperCase(char a){
	return (a>='A' && a <='Z'); 
}

char *getId(char*stock){
	int a = rand()%10; 
	int b = rand()%10; 
	int c = rand()%10; 
	char id[101]; 
	sprintf(id, "%c%c%d%d%d", 
		isUpperCase(stock[0]) ? stock[0] : stock[0] - 32,
		isUpperCase(stock[1]) ? stock[1] : stock[1] - 32,
		a, b, c); 
		
	return id; 
}

int findMax(int a, int b){
	if(a>b){
		return a; 
	} else {
		return b; 
	}
}

int getHeight(Node * root){
	if(root== NULL){
		return 0; 
	} else {
		return root->height; 
	}
}

void updateHeight(Node*root){
	root->height = findMax(getHeight(root->left), getHeight(root->right))+1;
}

int getBF(Node * root){
	if(root==NULL){
		return 0; 
	} else {
		return getHeight(root->left) - getHeight(root->right); 
	}
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
	root->left = rightLeft; 
	
	updateHeight(root); 
	updateHeight(right);
	
	return right;
}

Node * balancing(Node * root){
	updateHeight(root);
	int bf = getBF(root); 
	
	if(bf > 1){
		if(getBF(root->left)>0){
			// LL Rotation
			root = rightRotate(root); 
		} else {
			// LR Rotation
			root->left = leftRotate(root->left); 
			root = rightRotate(root); 
		}
	} else if(bf < -1){
		if(getBF(root->right) <0){
			// RL Rotation
			root = leftRotate(root); 
		} else {
			// RL Rotation
			root->right = rightRotate(root->right); 
			root = leftRotate(root); 
		}
	}
	return root; 
}

Node * push(Node *root, Node * newNode){
	if (root == NULL) {
		printf("Selamat berhasil masuk, saham Id : %s\n", newNode->id); 
		return newNode; 
	}
	
	if(strcmp(root->stock, newNode->stock) > 0){
		root->left = push(root->left, newNode); 
	} else if(strcmp(root->stock, newNode->stock) < 0){
		root->right = push(root->right, newNode); 
	} else {
		printf("Maaf saham dengan id [%s] tidak berhasil masuk kedalam data\n", newNode->id); 
		return root; 
	}
	
	return balancing(root); 
}

void addStock(){
	char stock[101]; 
	printf("Kode Saham: "); 
	scanf("%[^\n]", &stock); 
	getchar(); 
	
	double price; 
	printf("price: "); 
	scanf("%lf", &price); 
	getchar();
	
	int volume; 
	printf("Volume: "); 
	scanf("%d", &volume);  
	getchar(); 
	
	char id[101]; 
	strcpy(id, getId(stock)); 
	
	int portofolio = 0; 
	portofolio = price * volume; 
	
	root = push(root, createNode(stock, id, portofolio, price, volume)); 
}

void inOrder(Node * root){
	if(root){
		inOrder(root->left);  
		printf("| %-7s | %-6s | %-10.2f | %-10d | %-10d |\n", root->id, root->stock, root->price, root->volume, root->portofolio); 
		inOrder(root->right); 
	}
}

void preOrder(Node * root){
	if(root){
		printf("| %-7s | %-6s | %-10.2f | %-10d | %-10d |\n", root->id, root->stock, root->price, root->volume, root->portofolio); 
		preOrder(root->left); 
		preOrder(root->right); 
	}
}

void postOrder(Node * root){
	if(root){
		postOrder(root->left); 
		postOrder(root->right); 
		printf("| %-7s | %-6s | %-10.2f | %-10d | %-10d |\n", root->id, root->stock, root->price, root->volume, root->portofolio); 
	}
}

void listPortofolio(){
	if(root ==  NULL){
		puts("Belum melakukan investasi"); 
		return; 
	}
	
	int opt1;
	do {
		puts("1. In-Order"); 
		puts("2. Pre-Order"); 
		puts("3. Post-Order"); 
		puts("4. Back MainMenu"); 
		printf(">> "); 
		scanf("%d", &opt1); 
		getchar(); 
		
		system("cls"); 
		switch(opt1){
			case 1: 
				{
					puts("====================================================================="); 
					printf("| %-7s | %-6s | %-10s | %-10s | %-10s |\n", "ID", "STOCK", "PRICE", "VOLUME", "TOTAL"); 
					puts("====================================================================="); 
				}
				inOrder(root);
				break; 
				
			case 2: 
				{
					puts("====================================================================="); 
					printf("| %-7s | %-6s | %-10s | %-10s | %-10s |\n", "ID", "STOCK", "PRICE", "VOLUME", "TOTAL"); 
					puts("====================================================================="); 
				}
				preOrder(root); 
				break; 
				
			case 3: 
				{
					puts("====================================================================="); 
					printf("| %-7s | %-6s | %-10s | %-10s | %-10s |\n", "ID", "STOCK", "PRICE", "VOLUME", "TOTAL"); 
					puts("====================================================================="); 
				}
				postOrder(root); 
				break;
				
			case 4: 
				break; 
				
			default:
				puts("Invalid Input"); 
				system("cls"); 
				break;  
		}
	}while(opt1 != 4); 
}

Node * searching(Node * root, char * id){
	if(root == NULL){
		return NULL;
	} else if(strcmp(root->id, id) < 0){
		return root->left =  searching(root->left, id); 
	} else if(strcmp(root->id, id) > 0){
		return root->right = searching(root->right, id); 
	} else {
		return root; 
	}
}

void updateStock(){
	if(root==NULL){
		puts("Belum melakukan investasi"); 
		return; 
	}
	
	inOrder(root); 
	
	char idToSearch[101]; 
	printf("Input Id want to change: ");
	scanf("%[^\n]", idToSearch); 
	getchar(); 
	
	Node *result = searching(root, idToSearch); 
	if(result == NULL){
		printf ("Data tidak ketemu saham dengen id : %s\n", idToSearch); 
	} else {
		double price1; 
		int volume1; 
		
		printf("Price: "); 
		scanf("%lf", &price1); 
		getchar(); 
		
		printf("Volume: "); 
		scanf("%d", &volume1); 
		getchar(); 
		
		int portofolio1 = price1 * volume1; 
		
		result->price = price1; 
		result->volume = volume1; 
		result->portofolio = portofolio1; 
		
		inOrder(root); 
	}
}

Node * pop(Node * root, char * id){
	if(root == NULL){
		return NULL; 
	}
	if(strcmp(root->id, id) > 0){
		root->left = pop(root->left, id); 
	} else if(strcmp(root->id, id) < 0){
		root->right = pop(root->right, id); 
	} else {
		if(root->right == NULL && root->left == NULL){
			free(root); 
			return NULL;  
		} else if(root->right == NULL && root->left != NULL){
			Node * temp = root->left; 
			free(root); 
			return temp;
		}else if(root->right != NULL && root->left == NULL){
			Node * temp = root->right;
			free(root);
			return temp;
		} else {
			Node * predessecor = root->left; 
			
			while(predessecor->right != NULL){
				predessecor = predessecor->right; 
			}
			
			strcpy(root->id, predessecor->id); 
			strcpy(root->stock, predessecor->stock); 
			root->portofolio = predessecor->portofolio; 
			root->price = predessecor->price;
			root->volume = predessecor->volume; 
			
			root->left = pop(root->left, predessecor->id);
			
		}
	}
	return balancing(root); 
}

void deleteStock(){
	if(root == NULL){
		puts("Belum melakukan investasi"); 
		return; 
	} 
	
	inOrder(root); 
	
	char idtodelete[101];
	printf("ID Want To Delete: "); 
	scanf("%[^\n]", &idtodelete); 
	getchar(); 
	
	Node * result1 = searching(root, idtodelete); 
	if(result1 == NULL){
		printf ("Data tidak ketemu saham dengen id : %s\n", idtodelete); 
	} else {
		root = pop(root, idtodelete); 
		inOrder(root); 
	}
}

void mainMenu(){
	int opt; 
	do{
		puts("Jelvis Portofolio"); 
		puts("============================="); 
		puts("1. Add Stock"); 
		puts("2. List Portofolio"); 
		puts("3. Update Stock"); 
		puts("4. Delete Stock"); 
		puts("5. Exit"); 
		printf(">> "); 
		scanf("%d", &opt); 
		getchar(); 
		
		system("cls"); 
		switch(opt){
			case 1: 
				addStock(); 
				break; 
				
			case 2: 
				listPortofolio(); 
				break; 
				
			case 3:
				updateStock(); 
				break; 
				
			case 4: 
				deleteStock(); 
				break; 
				
			case 5: 
				puts("Terimakasih"); 
				break; 
				
			default: 
				puts("Invalid Input"); 
				break; 
		}
	} while(opt != 5); 
}

int main(){
	mainMenu(); 
	return 0; 
}
