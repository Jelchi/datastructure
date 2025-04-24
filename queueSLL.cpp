#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

struct Node {
    char name[101]; 
    int id; 
    Node * next; 
}; 

Node * front = NULL; 
Node * rear = NULL; 

Node *createNode (const char *name, int id){
    Node *newNode = (Node*)malloc(sizeof(Node)); 
    strcpy(newNode->name, name); 
    newNode->id = id;
    newNode->next =  NULL; 

    return newNode; 
}

void pushTail(const char * name, int id){
    Node *newNode = createNode(name, id); 

    if(front == NULL){
        front = rear = newNode; 
    } else {
        rear->next = newNode; 
        rear = newNode; 
    }
}

void addPerson(){
    char name[101]; 
    int id; 

    printf("Input name: "); 
    scanf("%[^\n]", &name); 
    getchar(); 

    printf("Input id: "); 
    scanf("%d", &id); 
    getchar(); 

    pushTail(name, id); 
}

void popHead(){
    if(front == NULL){
        puts("Tidak ada data"); 
        return; 
    } else if(front == rear){
        free(front); 
        front = rear = NULL; 
    } else {
        Node *temp = front; 

        front = temp->next; 
        free(temp); 
        temp = NULL; 
    }
}

void display(){
    if(front == NULL){
        puts("Data Kosong"); 
        return; 
    } else {
        puts("Taylor Swift List Queue"); 
        puts("========================"); 
        Node *curr = front; 
        while(curr != NULL){
            printf("Name: %s\n", curr->name); 
            printf("Id: %d\n", curr->id);
            curr = curr->next;  
        }
    }
}

void menu(){
    int opt; 
    do{
        puts("Taylor Switch Queue"); 
        puts("===================");
        puts("1. ADD PERSON"); 
        puts("2. CANCEL PERSON"); 
        puts("0. DISPLAY"); 
        puts("3. EXIT"); 
        printf(">> "); 
        scanf("%d", &opt); 
        getchar();

        system("cls"); 
        switch(opt){
            case 1: 
                addPerson(); 
                break; 

            case 2: 
                popHead(); 
                break; 

            case 3: 
                puts("Terimakasih");
                system("pause");  
                break; 

            case 0: 
                display(); 
                system("pause"); 
                break; 
                
            default: 
            puts("Invalid Error"); 
            system("pause"); 
            break; 
        }
        system("cls"); 
    }while(opt != 3); 
}

int main(){
    menu(); 
    return 0; 
}