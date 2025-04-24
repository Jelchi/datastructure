#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 
#define SIZE 5
int nodeCount = 0; 

struct Node {
    char name[101];
    Node * next;
}; 
Node *head[SIZE]; 
Node *tail[SIZE]; 

Node *createNode(const char *name){
    Node *newNode = (Node*)malloc(sizeof(Node)); 
    strcpy(newNode->name, name);
    newNode->next = NULL; 

    return newNode; 
}

int hash(const char *name){
    return strlen(name)%SIZE; 
}

void push(const char *name){
    int key = hash(name); 

    Node * newNode = createNode(name); 
    if(head[key] == NULL){
        head[key] = tail[key] = newNode; 
    } else {
        tail[key]->next = newNode; 
        tail[key] = newNode; 
    }
    nodeCount++; 
}

void pop(const char *name){
    int key = hash(name); 
    
    if(head[key]== NULL){
        puts("Data kosong"); 
        return; 
    } else if(head[key]==tail[key]){
        free(head[key]); 
        head[key]= tail[key]= NULL; 
    } else if(strcmp(name, head[key]->name)==0){
        Node * temp = head[key]; 
        head[key] = head[key]->next;
        free(temp); 
        temp = NULL;
    } else if(strcmp(name, tail[key]->name)==0){
        Node *temp = head[key]; 
        while(temp->next != NULL && strcmp(name, temp->next->name)!= 0){
            temp = temp->next; 
        }
        tail[key] = temp; 
        free(temp->next);
        temp->next = NULL;
    }
}

void display(){
    if(nodeCount == 0){
        puts("Tidak ada data"); 
    } else {
        for(int i=0; i<SIZE; i++){
            if(head[i] != NULL){
                printf("%d. ", i); 

                Node * curr = head[i];
                while(curr != NULL){
                    printf("%s ->", curr->name); 
                    curr = curr->next; 
                }
                printf("\n");; 
            }
        }
    }
}

void mainMenu(){
    int opt; 
    do{
        puts("1. Input Data"); 
        puts("2. Delete Data"); 
        puts("3. Display"); 
        puts("0. Exit"); 

        printf(">> "); 
        scanf("%d", &opt); 
        getchar();

        system("cls");  

        switch(opt){
            case 1: 
                push("Hemnes");  
                push("Sprutt");
                push("Hodde");
                push("Dvala");
                push("Godmorgon");
                push("Aina");
                push("Sannolikt");
                push("Variera");
                push("Viktigt");
                push("Anvandbar");
                push("Vardagen");
                push("Alex");
                push("Malm");
                push("Micke");
                push("Svartasen");
                push("Skarsta");
                push("Stuva");
                push("Algot");
                push("Glotten");
                push("Gruntal");
                break; 

            case 2: 
                {
                    char name[101]; 
                    printf("Input name: "); 
                    scanf("%[^\n]", &name); 
                    pop(name); 
                }
                break; 

            case 3: 
                display();
                system("pause"); 
                break;

            case 0: 
                puts("Terimakasih"); 
                system("pause"); 
                break ;

            default: 
                puts("Invalid Input"); 
                break; 
            
        }
        system("cls"); 
    }while (opt != 4); 
}
int main (){ 
    mainMenu();
    
    return 0; 
}