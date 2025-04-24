#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#define SIZE 50

struct Node{
    char name[101]; 
    char type[101]; 
    int storage; 
    Node *next; 
}; 

Node  *head[SIZE]; 
Node *tail [SIZE]; 

int nodeCount = 0; 

Node *createNode(const char *name, const char * type, int storage){
    Node * newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name); 
    strcpy(newNode->type, type);
    newNode->storage = storage;
    newNode->next = NULL;

    return newNode;
}

int hash(const char *name){
    int result = 0; 

    for(int i=0; i<strlen(name); i++){
        result += name[i]; 
    }
    return result % SIZE; 
}

void push(const char *name, const char *type, int storage){
    Node * newNode = createNode(name , type, storage); 
    int key = hash(name); 

    if(head[key] == NULL){
        head[key] = tail[key] = newNode;  
    } else if(strcmp(name, head[key]->name) <0){
        newNode->next = head[key];
        head[key] = newNode; 
    } else if(strcmp(name, tail[key]->name)>0){
        tail[key]->next = newNode; 
        tail[key] = newNode; 
    } else {
        Node * curr = head[key]; 
        while(curr->next != NULL && strcmp(name, curr->next->name)>= 0){
            curr = curr->next; 
        }
        newNode->next = curr->next; 
        curr->next = newNode; 
    }
}

void pop(const char *name){
    int key = hash(name);

    if(head[key] == tail[key] && strcmp(name, head[key]->name)==0){
        head[key] = tail[key] = NULL; 
    } else if(strcmp(name, head[key]->name)==0){
        Node * temp = head[key]; 
        head[key] = head[key]->next; 
        free(temp); 
        temp = NULL; 
    } else if(strcmp(name, tail[key]->name)==0){
        Node * curr = head[key]; 

        while(curr->next != tail[key]){
            curr = curr->next; 
        }
        free(curr->next); 
        curr->next = NULL; 
        tail[key] = curr; 
    }
}

Node * searchNode(const char *name){
    int key = hash(name); 

    if(head[key] == NULL){
        return NULL; 
    } 

    Node * curr = head[key]; 
    while(curr != NULL & strcmp(name, curr->name)!=0){
        curr = curr->next;  
    }

    if(strcmp(name, curr->name) == 0){
        return curr; 
    } else {
        return NULL; 
    }
}

void diplayData(){
    if(nodeCount == NULL){
        puts("Datanya kosong"); 
    } else {
        for(int i=0; i< SIZE; i++){
            if(head[i]!=NULL){
                printf("%8s | %8s | %8s | %8s |\n", "Key", "name", "type", "duration"); 
                printf("%8d |", i); 

                Node * curr = head[i]; 
                while(curr != NULL){
                    printf("%8s |%8s |%8d\n", curr->name, curr->type, curr->storage); 
                    curr = curr->next; 
                }
            }
        }
    }
}

void insertData(){
    char name[101]; 
    char type[101]; 
    int storage; 
    int count;
    char confirmation; 

    do{
        printf("Input name vehicle[must be 2 word]: "); 
        scanf("%[^\n]", &name); 
        getchar(); 
  
        char *token = strtok (name, " "); 
        while(token!=NULL){
            count++; 
            token = strtok(NULL, " "); 
        }
    } while(count != 2); 

    do{
        printf("Input type vechile[must be between SUV, Sedan, Hatchback]: "); 
        scanf("%[^\n]", &type);
        getchar();  
    }while(strcmp(type, "SUV")!=0  && strcmp(type, "Sedan")!=0 && strcmp(type,"Hatchback")!=0);

    do{
        printf("Input storage duration [must be positive]: "); 
        scanf("%d", &storage); 
        getchar(); 
    }while(storage < 0); 

    do{
        printf("Are you sure? [y/n]: "); 
        scanf("%c", &confirmation);
    }while(confirmation != 'y' && confirmation != 'n');

    if(confirmation == 'y'){
        nodeCount++; 
        push(name, type, storage);
        puts("Berhasil masuk");  
    }
}


void updateData(){
    char updateName[101]; 
    do{
        printf("Input name: "); 
        scanf("%s", &updateName); 
        getchar(); 
    }while(strlen(updateName) == NULL);
    
    Node *node = searchNode(updateName); 
    int duration;
    if(node){
            do{
            printf("Input Duration: "); 
            scanf("%d", &duration); 
            getchar(); 
        } while(duration <0); 
        node->storage = duration; 
    } else {
        puts("Invalid Input"); 
    }
}

void mainMenu(){
    int opt; 
    do {
        puts("1. Insert New Vehicle");
        puts("2. View ALl Vehicle"); 
        puts("3. Update Stroge"); 
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
                diplayData(); 
                break; 

            case 3: 
                updateData(); 
                break; 

            case 4: 
                char name[101]; 
                printf("Input name: "); 
                scanf("%[^\n]", &name); 
                getchar(); 
                pop(name); 

            case 5: 
            puts("Terimakasih "); 
            break; 

            default: 
            puts("Invalid Input");
            break; 
        }
    }while (opt != 4); 
}


int main(){
    mainMenu(); 
    return 0; 
}