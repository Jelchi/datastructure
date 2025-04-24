#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50

struct Vehicle {
	char name[64];
	char type[16];
	int duration;
	Vehicle* prev;
	Vehicle* next;
};

Vehicle* head[SIZE];
Vehicle* tail[SIZE];

int nodesCount = 0;

Vehicle* createNode(char name[], char type[], int duration) {
	Vehicle* newNode = (Vehicle*) malloc(sizeof(Vehicle));
	
	strcpy(newNode->name, name);
	strcpy(newNode->type, type);
	newNode->duration = duration;
	newNode->prev = newNode->next = NULL;
	
	return newNode;
}

int hash(char name[]) {
	int sum = 0;
	for (int i = 0; i < strlen(name); i++) {
		sum += name[i];
	}
	return sum % SIZE;
}

void push(char name[], char type[], int duration) {
	int key = hash(name);
	
	Vehicle* newNode = createNode(name, type, duration);
	
	if (head[key] == NULL) {
		head[key] = tail[key] = newNode;
	} else {
		if (strcmp(name, head[key]->name) < 0) {
			newNode->next = head[key];
			head[key]->prev = newNode;
			head[key] = newNode;
		} else if (strcmp(name, tail[key]->name) > 0) {
			newNode->prev = tail[key];
			tail[key]->next = newNode;
			tail[key] = newNode;
		} else {
			Vehicle* cur = head[key];
			// c
			// a b c c d e
			while (cur->next != NULL && strcmp(name, cur->next->name) >= 0) {
				cur = cur->next;
			}
			newNode->next = cur->next;
			newNode->prev = cur;
			cur->next->prev = newNode;
			cur->next = newNode;
		}
	}
}

Vehicle* searchNode(char name[]) {
	int key = hash(name);
	
	if (head[key] == NULL) {
		return NULL;
	}
	 
	Vehicle* cur = head[key];
	while (cur != NULL && strcmp(name, cur->name) != 0) {
		cur = cur->next;
	}
	
	if (strcmp(name, cur->name) == 0) {
		return cur;
	} else {
		return NULL;
	}
}

void display() {
	if (nodesCount == 0) {
		puts("There is no data to display.");
	} else {
		for (int i = 0; i < SIZE; i++) {
			if (head[i] != NULL) {
				printf("%d. ", i);
				
				Vehicle* cur = head[i];
				while (cur != NULL) {
					printf("%s %s %d -> ", cur->name, cur->type, cur->duration);
					cur = cur->next;
				}
			}
		}
	}
	
	system("pause");
}

void insert() {
	char name[64];
	char type[16];
	int duration;
	
	int words;
	do {
		words = 0;
		
		printf("Input vehicle name [must 2 words | unique]: ");
		scanf("%[^\n]", name);
		getchar();
		
		char copiedName[255];
		strcpy(copiedName, name);
		char *token = strtok(copiedName, " ");
		while (token != NULL){
			words ++;
			token = strtok(NULL, " ");
		}
		
		
//		// [ Toyota]
//		for (int i = 0; i < strlen(name); i++) {
//			if (name[i] == ' ' && (i + 1 < strlen(name) && name[i + 1] != ' ') && 
//				(i - 1 >= 0 && name[i - 1] != ' ')) {
//					spaceCount++;
//			}
//		}
	} while (words != 2 || searchNode(name) != NULL);
	
	do {
		printf("Input vehicle type [SUV | Sedan | Hatchback]: ");
		
		scanf("%s", type);
		getchar();
	} while (strcmp(type, "SUV") != 0 && strcmp(type, "Sedan") != 0 && strcmp(type, "Hatchback") != 0);
	
	do {
		printf("Input storage duration [must be positive]: ");
		
		scanf("%d", &duration);
		getchar();
	} while (duration <= 0);
	
	char confirmation;
	do {
		printf("Do you want to confirm insert [Y/N]: ");
		
		scanf("%c", &confirmation);
		getchar();
	} while (confirmation != 'Y' && confirmation != 'N');
	
	if (confirmation == 'Y') {
		nodesCount++;
		push(name, type, duration);
		puts("Data inserted successfully.");
	}
	
	system("pause");
}

void update() {
	char name[64];
	
	do {
		printf("Input name to be updated: ");
		scanf("%[^\n]", name);
		getchar();
	} while (searchNode(name) == NULL);
	
	int newDuration;
	do {
		printf("Input storage duration [must be positive]: ");
		
		scanf("%d", &newDuration);
		getchar();
	} while (newDuration <= 0);
	
	Vehicle* node = searchNode(name);
	node->duration = newDuration;
	
	system("pause");
}

void menu() {
	int option;
	do {
		system("cls");
		
		puts("Hash Table");
		puts("=============");
		puts("1. Insert new vehicle");
		puts("2. View all vehicles");
		puts("3. Update vehicle information");
		puts("4. Exit");
		
		scanf("%d", &option);
		getchar();
		
		switch (option) {
			case 1:
				insert();
				break;
			case 2:
				display();
				break;
			case 3:
				update();
				break;
			case 4:
				break;
			default:
				break;
		}
	} while (option != 4);
}

int main() {
	menu();
	return 0;
}