#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <time.h>

struct Node{
    char id[101]; 
    char name[101]; 
    char type[101];
    char email[101];
    int qty; 
    int price; 

    int height; 
    Node *left; 
    Node *right;  
}; 

void mainMenu();

Node * root = NULL; 

Node * createNode(char * id, char *name, char *type, char*email, int qty, int price){
    Node * newNode  = (Node*)malloc(sizeof(Node)); 
    strcpy(newNode->id, id); 
    strcpy(newNode->name, name); 
    strcpy(newNode->type, type); 
    strcpy(newNode->email, email);
    newNode->qty = qty; 
    newNode->price = price; 

    newNode->height = 1; 
    newNode->left = NULL; 
    newNode->right = NULL; 
    return newNode; 
}

char * getId(char *type){
    int a = rand()%10; 
    int b = rand()%10; 
    int c = rand()%10; 

    char *id = (char *) malloc(101 * sizeof(char)); 
    if(strcmp(type, "Ice Cream")==0){
        sprintf(id,"IC%d%d%d", a, b, c); 
    } else if(strcmp(type, "Milk Tea") == 0){
        sprintf(id, "MT%d%d%d", a,b,c); 
    } else if(strcmp(type, "Fruit Tea") == 0){
        sprintf(id, "FT%d%d%d", a,b,c); 
    }
    return id; 
}

int findMax (int left, int right){
    if(left>right){
        return left; 
    }
    return right; 
}

int getHeight(Node * root){
    if(root == NULL){
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

Node* rightRotate(Node * root){
    Node * left = root->left; 
    Node * leftRight = left->right; 

    left->right = root; 
    root->left = leftRight; 

    updateHeight(root); 
    updateHeight(left); 

    return left; 
}

Node * leftRotate(Node *root){
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
            root = rightRotate(root);
        }
    }
    return root; 
}

Node * insertion(Node * current, Node *newNode){
    if(current == NULL) return newNode; 

    if(strcmp(current->id, newNode->id) > 0 ){
        return current -> left = insertion(current->left, newNode); 
    } else if(strcmp(current->id, newNode->id) < 0){
        return current -> right = insertion(current->right, newNode); 
    }
    return balancing(root); 
}

Node * searchingName(Node * root, char * name){
    if(root == NULL) return NULL; 

    if(strcmp(root->name, name) == 0){
        return root; 
    } else if(strcmp(name, root->name) < 0){
        return searchingName(root->left, name);
    } else if(strcmp(name, root->name) > 0){
        return searchingName(root->right, name); 
    }
}

bool checkingEmail(char * email){
    int lenEmail = strlen(email); 
    int atIdx = -1; 
    int dotIdx = -1; 

    for(int i=0; i<lenEmail; i++){
        if(email[i] == '@'){
            atIdx = i; 
        }

        if(email[i] == '.'){
            dotIdx = i; 
        }
    }

    if(strncmp(email+dotIdx, ".com", 4) != 0){
        return false; 
    }

    if(atIdx != 0 && atIdx < dotIdx -1 && dotIdx == lenEmail - 4){
        return true;
    }
    return false; 
}

void insertTransaction(){
    char name[101]; 
    char tempName[101]; 
    int word; 

    do{
        word = 0; 
        printf("Input Name: "); 
        scanf("%[^\n]", &name); 
        getchar(); 

        strcpy(tempName, name); 
        char *token = strtok(tempName, " "); 
        while(token != NULL){
            word++; 
            token = strtok(NULL, " "); 
        }
    }while(word !=2 || searchingName(root, name) != 0); 

    char type[101]; 

    do{
        printf("Input Product Type: ");
        scanf("%[^\n]", &type); 
        getchar(); 
    }while(strcmp(type, "Ice Cream")!= 0 && strcmp(type, "Fruit Tea")!=0 && strcmp(type , "Milk Tea")!=0); 

    char email[101]; 
    
    do{
        printf("Input Email [emailAddress@[domain].com]: "); 
        scanf("%[^\n]", &email); 
        getchar(); 
    } while(!checkingEmail(email)); 

    int qty; 

    do{
        printf("Input quantity: "); 
        scanf("%d", &qty); 
        getchar();
    } while(qty <= 0); 

    int price = 0; 
    if(strcmp(type, "Ice Cream") == 0){
        price = 15000 * qty; 
    } else if(strcmp(type, "Milk Tea") == 0){
        price = 20000 * qty;
    } else if(strcmp(type, "Fruit Tea") == 0){
        price = 25000 * qty; 
    }

    char id[101]; 
    strcpy(id, getId(type)); 
    
    root = insertion(root, createNode(id, name, type, email, qty, price)); 
    printf("Insert Successful\n");
    system("pause");
}

Node * searchingId(Node*root, char *id){
    if(root == NULL) return NULL; 

   	if(strcmp(id, root->id) <0){
        searchingId(root->left, id); 
    } else if(strcmp(id, root->id)>0){
        searchingId(root->right, id); 
    } else if(strcmp(id,root->id)==0) {
    	return root; 
	}
    
}

void displayTransaction(Node * root){
    if(root == NULL){
        puts("No Transaction"); 
        return; 
    } else {
        puts("All Transaction: "); 
        puts("========================"); 
        printf("Id: %s\nName: %s\nType: %s\nEmail: %s\nQuantity: %d\nPrice: %d\n", root->id, root->name, root->type, root->email, root->qty, root->price);
    }
    if(root->left) displayTransaction(root->left); 
    if(root->right) displayTransaction(root->right);
    puts(" ");  
}

void updateTransaction(){
    displayTransaction(root);  
    
    char idToSearch[101]; 
    printf("Input Id to Searching: "); 
    scanf("%[^\n]", idToSearch); 
    getchar(); 

    Node* result = searchingId(root, idToSearch);
    
    if(result == NULL){
        puts("Not founded"); 
        return; 
    }
	char nameToChange[101]; 
    char tempNameToChange[101]; 
	int word2; 
	do{
	    word2= 0; 
	    printf("Input Name To Change: ");
	    scanf("%[^\n]", &nameToChange); 
	    getchar(); 
		
	    strcpy(tempNameToChange, nameToChange); 
	    char *token1 = strtok(tempNameToChange, " "); 
		 
		while(token1 != NULL){
		    word2++; 
		    token1 = strtok(NULL, " "); 
	    }
	} while(word2 != 2 || searchingName(root, nameToChange) != NULL); 
	strcpy(result->name, nameToChange); 
}

Node * getSuccesor(Node * root){
	root = root->right; 
	
	while(root->left != NULL){
		root = root->left; 
	}
	return root; 
}

Node * deletion(Node * current, char *id){
	if(current == NULL){
		puts("Not Founded\n"); 
		return NULL; 
	} else if(strcmp(current->id, id) > 0){
		current->left = deletion(current->left, id);
	} else if(strcmp(current->id, id) <0){
		current->right = deletion(current->right, id ); 
	} else {
		if(current->left==NULL &&current->right ==NULL){
			free(current); 
			return NULL; 
		} else if(current->left == NULL && current->right != NULL){
			Node *temp = current;
			current = current->right; 
			free(temp); 
		} else if(current->left != NULL && current->right == NULL){
			Node *temp = current;
			current = current->left; 
			free(temp); 
		} else {
			Node * temp = getSuccesor(current);
			strcpy(current->id, temp->id); 
			strcpy(current->name, temp->id); 
			strcpy(current->type, temp->type); 
			strcpy(current->email, temp->email); 
			current->qty = temp->qty; 
			current->price = temp->price; 
			right
			current-> = deletion(current->right, temp->id); // if succesor, kalau predecessor dia ke kiri
			
		}
	}
	return balancing(current); 
}

void deleteTransaction(){
	displayTransaction(root);
	
	if(root == NULL) return; 
	
	char idToSearch[101]; 
	printf("Input Id: "); 
	scanf("%[^\n]", &idToSearch);
	getchar(); 
	
	root = deletion(root, idToSearch);  
	
}

void mainMenu(){
    int opt;
    
    do{
        puts("NiLue Apps Menu");
        puts("===================================="); 
        puts("1. Insert New Transaction"); 
        puts("2. View All Transactions"); 
        puts("3. Update Transaction Details"); 
        puts("4. Delete Transaction"); 
        puts("5. Exit"); 
        printf(">> "); 
        scanf("%d", &opt); 
        getchar(); 

        system("cls"); 
        switch(opt){
            case 1: 
                insertTransaction(); 
                break;
            
            case 2: 
                displayTransaction(root); 
                system("pause"); 
                break; 

            case 3:     
                updateTransaction(); 
                system("pause"); 
                break; 

            case 4: 
            	deleteTransaction(); 
            	system("pause"); 
            	
                break; 

            case 5: 
                puts("Thank You"); 
                system("pause"); 
                break; 

            default:
                puts("Invalid Input");
                system("pause");  
                break; 
        } 
        system("cls"); 
    }while(opt != 5); 
}

int main(){
    mainMenu();  
    return 0; 
}
