#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NAMA : FELIX SALIM
// KELAS : PPTI 19
// NIM : 2702363645

typedef struct Node Node;

struct Node {
	char symbol[255];
	double price;
	int volume, key, height;
	Node *left, *right;
};

Node *root = NULL;

int max(int a, int b) {
	return (a > b) ? a : b;
}

int getHeight(Node *root) {
	if (root == NULL) return 0;
	return root -> height;
}

int getBf(Node *root) {
	if (root == NULL) return 0;
	return getHeight(root -> left) - getHeight(root -> right);
}

void updateHeight(Node *root) {
	root -> height = max(getHeight(root -> left), getHeight(root -> right)) + 1;
}

Node *leftRotate(Node *root) {
	Node *right = root -> right;
	Node *leftGrand = right -> left;
	
	right -> left = root;
	root -> right = leftGrand;
	
	updateHeight(root);
	updateHeight(right);
	
	return right;
}

Node *rightRotate(Node *root) {
	Node *left = root -> left;
	Node *rightGrand = left -> right;
	
	left -> right = root;
	root -> left = rightGrand;
	
	updateHeight(root);
	updateHeight(left);
	
	return left;
}

int getKey(const char *symbol) {
	int sum = 0;
	for (int i = 0; i < strlen(symbol); i++) {
		sum += symbol[i];
	}
	
	return sum;
}

Node *createNode(const char *symbol, double price, int volume) {
	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode -> height = 1;
	newNode -> left = NULL;
	newNode -> right = NULL;
	strcpy(newNode -> symbol, symbol);
	newNode -> price = price;
	newNode -> volume = volume;
	newNode -> key = getKey(symbol);
	
	return newNode;
}

Node *balancing(Node *root) {
	if (root == NULL) {
		return NULL;
	}
	
	updateHeight(root);
	int bf = getBf(root);
	if (bf > 1) {
		int leftBf = getBf(root -> left);
		if (leftBf >= 0) {
			root = rightRotate(root);
		} else {
			root -> left = leftRotate(root -> left);
			root = rightRotate(root);
		}
	} else if (bf < -1) {
		int rightBf = getBf(root -> right);
		if (rightBf <= 0) {
			root = leftRotate(root);
		} else {
			root -> right = rightRotate(root -> right);
			root = leftRotate(root);
		}
	}
	
	return root;
}

Node *insert(Node *root, Node *newNode) {
	if (root == NULL) {
		printf("Success! Stock key (index): %d\n", newNode -> key);
		return newNode;
	}
	if (newNode -> key < root -> key) {
		root -> left = insert(root -> left, newNode);
	} else if (newNode -> key > root -> key) {
		root -> right = insert(root -> right, newNode);
	} else {
		printf("Failed! Stock key (index) of %d already exists!\n", newNode -> key);
		return root;
	}
	
	return balancing(root);
}

void add() {
	system("cls");
	char symbol[255];
	double price;
	int volume, key;
	
	printf("Enter stock symbol: ");
	scanf("%[^\n]", symbol); getchar();
	
	printf("Enter stock price: ");
	scanf("%lf", &price); getchar();
	
	printf("Enter stock volume: ");
	scanf("%d", &volume); getchar();

	root = insert(root, createNode(symbol, price, volume));
	system("pause");
}

void inorder(Node *root) {
	if (root == NULL) {
		return;
	}
	inorder(root -> left);
	printf("Key: %d | Symbol: %s, Price: %.2lf, Volume: %d\n", root -> key, root -> symbol, root -> price, root -> volume);
	inorder(root -> right);
}

void view() {
	system("cls");
	if (root == NULL) {
		printf("No stock exist!\n");
		system("pause");
		return;
	}
	inorder(root);
	system("pause");
}

Node *search(Node *root, int key) {
	if (root == NULL) {
		return NULL;
	}
	if (key < root -> key) {
		return search(root -> left, key);
	} else if (key > root -> key) {
		return search(root -> right, key);
	} else {
		return root;
	}
}

void update() {
	system("cls");
	if (root == NULL) {
		printf("No stock to update!\n");
		system("pause");
		return;
	}
	int key;
	double price;
	printf("Enter key to update: ");
	scanf("%d", &key); getchar();
	
	Node *res = search(root, key);
	
	if (res != NULL) {
		printf("Enter new stock price: ");
		scanf("%lf", &price); getchar();
		res -> price = price;
		printf("Symbol: %s, Price: %.2lf, Volume: %d\n", res -> symbol, res -> price, res -> volume);
	} else {
		printf("Stock with key: %d is not found\n", key);
	}
	system("pause");
}

Node *findPredecessor(Node *root) {
	Node *predecessor = root -> left;
	while (predecessor -> right != NULL) {
		predecessor = predecessor -> right;
	}
	return predecessor;
}

Node *deleteStock(Node *root, int key, int *success) {
	if (root == NULL) {
		*success = 0;
		printf("Stock with key: %d is not found\n", key);
		return NULL;
	}
	if (key < root -> key) {
		root -> left = deleteStock(root -> left, key, success);
	} else if (key > root -> key) {
		root -> right = deleteStock(root -> right, key, success);
	} else {
		if (root -> left == NULL && root -> right == NULL) {
			free(root);
			return NULL;
		} else if (root -> left == NULL && root -> right != NULL) {
			Node *temp = root -> right;
			free(root);
			return temp;
		} else if (root -> left != NULL && root -> right == NULL) {
			Node *temp = root -> left;
			free(root);
			return temp;
		} else {
			//predecessor deletion
			Node *predecessor = findPredecessor(root);
			root -> key = predecessor -> key;
			strcpy(root -> symbol, predecessor -> symbol);
			root -> price = predecessor -> price;
			root -> volume = predecessor -> volume;
			
			root -> left = deleteStock(root -> left, predecessor -> key, success);
		}
	}
	
	return balancing(root);
}

void del() {
	system("cls");
	if (root == NULL) {
		printf("No stock to delete\n");
		system("pause");
		return;
	}
	int key;
	int success = 1;
	printf("Enter key to delete: ");
	scanf("%d", &key); getchar();
	root = deleteStock(root, key, &success);
	if (success == 1) {
		printf("Deletion of stock with key: %d was successful\n", key);	
	}
	system("pause");
	view();
}

void showMenu() {
	system("cls");
	puts("Stock Market Analysis System");
	puts("1. Add Stock");
	puts("2. List Stocks");
	puts("3. Update Stock Price");
	puts("4. Delete Stock");
	puts("5. Exit");
}

void menu() {
	int run = 1;
	int ch;
	while (run) {
		showMenu();
		do {
			printf("Enter your choice: ");
			scanf("%d", &ch); getchar();
			if (ch < 1 || ch > 5) {
				printf("Invalid choice! Please try again.\n");
			}
		} while (ch < 1 || ch > 5);
		switch (ch) {
			case 1:
				add();
				break;
			case 2:
				view();
				break;
			case 3:
				update();
				break;
			case 4:
				del();
				break;
			case 5:
				run = 0;
				printf("I successfully completed The Stock Market Analysis System using AVL trees challenge from Professor Moneybags");
				break;
		}
	}
}

Node *freeRoot(Node *root) {
	if (root == NULL) return NULL;
	root -> left = freeRoot(root -> left);
	root -> right = freeRoot(root -> right);
	free(root);
	return NULL;
}

int main() {
	menu();
	root = freeRoot(root);
	
	return 0;
}

