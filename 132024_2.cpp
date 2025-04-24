#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

#define SIZE 10
int nodeCount = 0; 

struct Node{
    char name[101]; 
    int age; 
    Node *next;
    Node *prev; 
}; 

Node* head[SIZE]; 
Node* tail [SIZE]; 

Node*createNode(char *name, int age){
    Node * newNode = (Node*)malloc(sizeof(Node)); 
    strcpy(newNode->name, name); 
    newNode->age = age; 
    newNode->next = NULL; 
    newNode->prev = NULL;

    return newNode;
}

int hash(char *name){
    int result = 0; 

    for(int i=0; i<strlen(name); i++){
        result += name[i]; 
    }
    return result % SIZE; 
}

void push(char*name, int age){
    int key = hash(name); 

    Node *newNode = createNode(name , age );
    if(head[key]== NULL){
        head[key] = tail[key] = newNode; 
    } else if(strcmp(name, head[key]->name)<0){
        newNode->next = head[key];
        head[key]->prev = newNode; 
        head[key] = newNode; 
    } else if(strcmp(name, tail[key]->name)>0){
        tail[key]->next = newNode; 
        newNode->prev = tail[key]; 
        tail[key] = newNode; 
    } else {
        Node * curr = head[key]; 
        while(curr->next != NULL && strcmp(name, curr->next->name) >=0){
            curr = curr->next; 
        } 
        newNode->next = curr->next; 
        newNode->prev = curr;
        curr->next->prev = newNode;  
        curr->next = newNode; 
    }
}

void pop(char *name){
    int key = hash(name);

    if(head[key]== tail[key]){
        free(head[key]);
        head[key]= tail[key] = NULL;  
    } else if(strcmp(name, head[key]->name)==0){
        Node * temp = head[key]; 
        head[key] = temp->next; 
        free(temp); 
        temp = NULL; 
    } else if(strcmp(name, tail[key]->name)!=0){
        Node *temp = tail[key]; 
        tail[key] = temp->prev; 
        free(temp); 
        temp = NULL; 
    } else{
        Node * curr = head[key]; 
        while(curr->next != NULL && strcmp(name, curr->next->name)!=0){
            curr = curr->next; 
        }
        if(curr->next == NULL){
            curr->next->prev = curr->next; 
        } 
        if(curr->prev == NULL){
            curr->prev->next = curr->prev; 
        }

        free(curr); 
        curr = NULL;
    }
}

void display(){
    if(nodeCount == 0){
        puts("Kosong"); 
    } else {
        for(int i=0; i<SIZE; i++){
            if(head[i] != NULL){
                printf("%d ", i); 

                Node * curr = head[i]; 
                while(curr != NULL){
                    printf("%s %d\n", curr->name, curr->age); 
                    curr = curr->next; 
                }
            }
        }
    }
    system("pause"); 
}

Node*searchNode(char *name){
    int key = hash(name); 

    if(head[key]== NULL){
        return NULL; 
    }
    
    Node * curr = head[key]; 
    while(curr != NULL && strcmp(name, curr->name)!=0){
        curr = curr->next; 
    }

    if(strcmp(name, curr->name)==0){
        return curr; 
    } else {
        return NULL; 
    }

}

void insertData(){
    char name[101]; 
    int age; 
    
    int word; 
    do{
        word = 0; 
        printf("Input name [must be 2 word and unique]: "); 
        scanf("%[^\n]", name); 
        getchar(); 

        char * token = strtok(name, " "); 
        while(token != NULL){
            word++; 
            token = strtok(NULL, " "); 
        }
    }while(word != 2 || searchNode(name) != NULL); 

    do{
        printf("Input age [up to 18'y old]: "); 
        scanf("%d", &age); 
        getchar(); 
    } while(age < 18); 

    char confirmation; 

    do {
        printf("confirmation[y/n]: "); 
        scanf("%c", &confirmation); 
        getchar(); 
    } while(confirmation != 'y' && confirmation != 'n'); 

    if(confirmation ==  'y'){
        push(name, age); 
        nodeCount++;
        puts("berhasil masuk"); 
    } 
}

void update(){
    char updateName[101]; 
    char nameToUpdate[101]; 
    int ageToUpdate; 
    int word, word1;  
    do{
        printf("Input name [must  be 2 word and unique]: "); 
        scanf("%[^\n]", &updateName); 
        getchar(); 
        word = 0; 
        char * token = strtok(updateName, " ");
        while(token != NULL){
            word++; 
            token =  strtok(NULL, " "); 
        }
    }while(word !=2 && searchNode(updateName)!=0); 

    Node *node = searchNode(updateName); 

    if(node){
        do{
            printf("Input name want to change: "); 
            scanf("%[^\n]", &nameToUpdate); 
            getchar(); 
            char * token = strtok(nameToUpdate, " ");
            word1 =0; 
            while(token != NULL){
                word1++; 
                token =  strtok(NULL, " "); 
            }
        }while(word1 !=2 && searchNode(nameToUpdate)!=0); 

        do{
            printf("Input age to update: "); 
            scanf("%d", &ageToUpdate);
            getchar(); 
        }while(ageToUpdate<18); 
        
        strcpy(node->name, nameToUpdate); 
        node->age = ageToUpdate; 
    }
}

void mainMenu(){
    int opt; 
    do{
        puts("1. Insert Data"); 
        puts("2. View Data"); 
        puts("3. Delete"); 
        puts("4. Update Data"); 
        puts("EXIT"); 
        printf(">> "); 
        scanf("%d", &opt); 
        getchar(); 

        switch(opt){
            case 1: 
                insertData(); 
                break; 

            case 2: 
                display(); 
                break; 

            case 3: 
                char deleteName[101]; 
                printf("Input Name: ");
                scanf("%[^\n]", &deleteName); 
                getchar(); 
                pop(deleteName); 
                break; 

            case 4: 
                update();
                break; 
            
            case 5: 
                printf("terimakasih"); 
                break; 

            dafault: 
            printf("invalid error"); 
            break;         
        }
    }while(opt != 5); 
}

int main(){
    mainMenu(); 
    return 0;
}