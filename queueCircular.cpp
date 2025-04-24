#include <stdio.h>
#include <string.h> 
#include <stdlib.h> 

struct Node{
    char name[101];
    char nim[101]; 
    int age; 
    Node *next;
}; 

Node * front = NULL; 
Node * rear = NULL; 

Node *createNode(const char *name, const char *nim, int age){
    Node * newNode = (Node*)malloc(sizeof(Node)); 
    strcpy(newNode->name, name); 
    strcpy(newNode->nim, nim); 
    newNode->age = age; 
    newNode->next = NULL;

    return newNode;  
}

void pushTail(const char *name, const char*nim, int age){
    Node * newNode = createNode(name, nim, age); 

    if(front == NULL){
        front = rear = newNode; 
        rear->next = front; 
    } else {
        rear->next = newNode;
        rear = newNode; 
        rear->next = front; 
    }
}

void display(){
    if(front == NULL){
        puts("Data kosong"); 

        return; 
    } else {
        Node *curr = front; 
        Node *origin = front;
        
        puts("Data Siswa: ");
        while(curr != NULL){
            printf("Name: %s\n", curr->name); 
            printf("NIM: %s\n", curr->nim); 
            printf("Age: %d\n", curr->age); 
            puts("==================================="); 
            curr = curr->next; 

            if (curr==origin) {
                return;
            }
        } 
    }
}

void popHead(){
    if(front == NULL){
        puts("Data kosong"); 
    } else if(front == rear){
        free(front); 
        front = rear = NULL; 
    } else {
        Node * temp = front;

        front = temp->next; 
        rear->next = front; 
        free(temp); 
    }
}

void mainMenu(){
    int opt; 
    do{
        puts("Monopoly PPTI 19 Queue: "); 
        puts("1. Input Data");
        puts("2. Delete Queue"); 
        puts("3. EXIT"); 
        puts("0. Dipslay"); 

        printf(">> "); 
        scanf("%d",&opt); 
        getchar(); 

        system("cls"); 
        switch(opt){
            case 1: 
                pushTail("Jelvis", "2702365190", 19); 
                pushTail("Jelena", "240205290", 19); 
                pushTail("Donney", "2712331190", 21); 
                pushTail("Ashley", "271231240", 22); 
                pushTail("Kelvin", "27012341290", 19);
                break; 

            case 2: 
                popHead(); 
                break; 

            case 3: 
                puts("Terima Kasih"); 
                system("pause"); 
                break; 

            case 0: 
            display(); 
            system("pause");
            break; 

            default: 
            puts("Invalid Input"); 
            system("pause"); 
            break; 
        } 
        system("cls"); 
    }while(opt != 3); 
}


int main (){
    mainMenu(); 
    return 0; 
}