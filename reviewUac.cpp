#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Product{
	char id[10];
	char name[100];
	char type[100];
	char email[100];
	int quantity;
	int price;
	Product *left, *right;
	int height;
};

Product *root = NULL;

Product *newProduct(char *id, char *name, char *type, char *email, 
			int quantity, int price){
	Product *product = (Product*)malloc(sizeof(Product));
	strcpy(product->id, id);
	strcpy(product->name, name);
	strcpy(product->type, type);
	strcpy(product->email, email);
	product->quantity = quantity;
	product->price = price;
	product->left = product->right = NULL;
	product->height = 1;
	return product;
}

int height(Product *root){
	if(!root){
		return 0;
	}
	return root->height;
}

int max(int a, int b){
	return a > b ? a : b;
}

int getBalance(Product *root){
	if(!root){
		return 0;
	}
	return height(root->left) - height(root->right);
}

Product *rightRotate(Product *x){
	Product *y = x->left;
	Product *z = y->right;
	
	y->right = x;
	x->left = z;
	
	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));
	
	return y;
}

Product *leftRotate(Product *x){
	Product *y = x->right;
	Product *z = y->left;
	
	y->left = x;
	x->right = z;
	
	x->height = 1 + max(height(x->left), height(x->right));
	y->height = 1 + max(height(y->left), height(y->right));
	
	return y;
}

Product *checkBalance(Product *root){
	root->height = 1 + max(height(root->left), height(root->right));
	int balance = getBalance(root);
	
	// Left left
	if(balance > 1 && getBalance(root->left) >= 0){
		return rightRotate(root);
	}
	// Right Right
	else if(balance < -1 && getBalance(root->right) <= 0){
		return leftRotate(root);
	}
	// Left Right
	else if(balance > 1 && getBalance(root->left) < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	// Right Left
	else if(balance < -1 && getBalance(root->right) > 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}

Product *insert(Product *root, char *id, char *name, char *type, char *email, 
			int quantity, int price){
	// Kalau kosong
	if(!root){
		return newProduct(id, name, type, email, quantity, price);
	}
	// Kalau new id < root id
	else if(strcmp(id, root->id) < 0 ){
		root->left = insert(root->left, id, name, type, email, quantity, price);
	}
	// Kalau new id > root id
	else if(strcmp(id, root->id) > 0){
		root->right = insert(root->right, id, name, type, email, quantity, price);
	}
	return checkBalance(root);
}

char *getId(char type[]){
	int a = rand()%10;
	int b = rand()%10;
	int c = rand()%10;
	
	char id[10];
	if(strcmp(type, "Ice Cream") == 0){
		sprintf(id, "IC%d%d%d", a, b, c);
	}
	else if(strcmp(type, "Milk Tea") == 0){
		sprintf(id, "MT%d%d%d", a, b, c);
	}else if(strcmp(type, "Fruit Tea") == 0){
		sprintf(id, "FT%d%d%d", a, b, c);
	}
	return id;
}

bool checkName(char* name){
	int counter = 0;
	int x = 0;
	int len = strlen(name);
	for(int i = 0;i<len;i++){
		if(name[i] == ' '){
			x = 0;
		}
		else if(x == 0){
			counter++;
			x = 1;
		}
	}
	if(counter < 2) return false;
	return true;
}

bool checkUnique(Product* root, char* name){
	if(root && strcmp(name, root->name) == 0) return false;
	if(root && !checkUnique(root->left, name)) return false;
	if(root && !checkUnique(root->right, name)) return false;

	return true;
}

bool checkType(char* type){
	return strcmp(type, "Ice Cream") == 0
	|| strcmp(type, "Milk Tea") == 0
	|| strcmp(type, "Fruit Tea") == 0;
}

bool checkEmail(char* email){
	int len = strlen(email);
	int atidx = 0;
	int dotidx = 0;
	for(int i=0;i<len;i++){
		if(email[i] == '@') atidx = i;
		else if(email[i] == '.') dotidx = i;
	}
	if(strncmp(email+dotidx, ".com", 4) != 0){
		return false;
	}
	if(atidx != 0 && atidx < dotidx-1 && dotidx == len-4) return true;
	return false;
}

void addProduct(){
	char name[100];
	do{
		printf("Product Name: ");
		scanf("%[^\n]", name);
		getchar();
	}while(!checkName(name) || !checkUnique(root, name));
	
	char type[100];
	do{
		printf("Product Type: ");
		scanf("%[^\n]", type);
		getchar();
	}while(!checkType(type));
	
	char email[100];
	do{
		printf("Email: ");
		scanf("%s", email);
		getchar();
	}while(!checkEmail(email));
	
	int quantity;
	do{
		printf("Quantity: ");
		scanf("%d", &quantity);
		getchar();
	}while(quantity < 1);
	
	int price;
	if(strcmp(type, "Ice Cream") == 0){
		price = 15000 * quantity;
	}
	else if(strcmp(type, "Milk Tea") == 0){
		price = 20000 * quantity;
	}
	else if(strcmp(type, "Fruit Tea") == 0){
		price = 25000 * quantity;
	}
	char id[10];
	strcpy(id, getId(type));
	root = insert(root, id, name, type, email, quantity, price);
}

// Pre Order
// In Order
// Post Order

void print(Product *root){
	if(root){
		print(root->left);
		printf("%s: %s\n", root->id, root->name);
		print(root->right);
	}
}

bool checkEmpty(){
	if(!root){
		printf("There is no data!\n");
		return true;
	}
	return false;
}

Product* search(Product* root, char* id){
	if(!root) return NULL;
	else if(strcmp(id, root->id) < 0) return search(root->left, id);
	else if(strcmp(id, root->id) > 0) return search(root->right, id);

	return root;
}

void updateProduct(){
	print(root);
	char id[10];
	printf("Enter ID: ");
	scanf("%s", id); getchar();
	Product* key = search(root, id);
	if(!key){
		printf("Not found!\n");
		return;
	}
	char name[100];
	do{
		printf("Product Name: ");
		scanf("%[^\n]", name);
		getchar();
	}while(!checkName(name) || !checkUnique(root, name));
	strcpy(key->name, name);
}

Product* del(Product* root, char *id){
	if(!root){
		printf("Not Found!\n");
		return NULL;
	}
	else if(strcmp(id, root->id) < 0) root->left = del(root->left, id);
	else if(strcmp(id, root->id) > 0) root->right = del(root->right, id);

	else{
		if(!root->left && !root->right){
			free(root);
			return NULL;
		}
		else if(!root->left || !root->right){
			Product* child;
			if(root->left) child = root->left;
			else child = root->right;

			free(root);
			root = child;
		}
		else{
			Product* successor = root->right;
			while(successor->left){
				successor = successor->left;
			}

			strcpy(root->id, successor->id);
			strcpy(root->name, successor->name);
			strcpy(root->type, successor->type);
			strcpy(root->email, successor->email);
			root->quantity = successor->quantity;
			root->price = successor->price;

			root->right = del(root->right, successor->id);
		}
	}
	return checkBalance(root);

}

void deleteProduct(){
	print(root);
	char id[10];
	printf("Enter ID: ");
	scanf("%s", id); getchar();
	root = del(root, id);
}

void mainMenu(){
	while(true){
		printf("1. Insert\n");
		printf("2. Update\n");
		printf("3. Delete\n");
		printf("4. View\n");
		printf("5. Exit\n");
		int a;
		do{
			printf(">> ");
			scanf("%d", &a);
			getchar();
		}while(a < 1 || a > 4);
		if(a == 1){
			addProduct();
		}
		else if(a == 2){
			if(checkEmpty()) continue;
			updateProduct();
		}
		else if(a == 3){
			if(checkEmpty()) continue;
			deleteProduct();
		}
		else if(a == 4){
			if(checkEmpty()) continue;
			print(root);
		}
		else if(a == 5) return;
	}
}

int main(){
	
	mainMenu();
	
}
