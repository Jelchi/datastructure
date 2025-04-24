#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

struct Node{
    char name[101];
    int weight; 
    Node * next; 
}; 
Node * top; 

Node * createNode(const char *name, int weight){
    Node *newNode = (Node*)malloc(sizeof(Node)); 
    strcpy(newNode->name, name); 
    newNode->weight = weight; 
    newNode->next = NULL; 

    return newNode; 
}

void pushHead(const char *name, int weight){
    Node *newNode = createNode(name, weight);

    if(top == NULL){
        top = newNode; 
    } else {
        newNode->next = top; 
        top = newNode; 
    }
}

void insertData(){
    char name[101]; 
    int weight; 

    printf("Input name: "); 
    scanf("%[^\n]", &name); 
    getchar(); 

    printf("Input Weight: "); 
    scanf("%d", &weight); 
    getchar(); 

    pushHead(name, weight); 
}

void popHead(){
    if(top == NULL){
        puts("Data kosong"); 
    } else {
        Node * temp = top; 
        top = top->next; 
        free(temp); 
        temp = NULL; 
    }
}

void display(){
    if(top == NULL){
        puts("data kosong"); 
        return; 
    } else {
        Node * curr = top; 

        while(curr != NULL){
            puts("Laundry Data: "); 
            printf("name: %s\n", curr->name); 
            printf("Weight: %d\n", curr->weight); 

            curr = curr->next; 
        }
    }
}

void menu(){
    int opt; 
    do{
        puts("Laundry Menu"); 
        puts("=========================="); 
        puts("1. Insert Data"); 
        puts("2. Finish Data");
        puts("0. Display");  
        puts("3. Exit"); 

        printf(">> "); 
        scanf("%d", &opt); 
        getchar(); 

        system("cls"); 
        switch(opt){
            case 1: 
                insertData(); 
                break;

            case 2: 
                popHead(); 
                break; 

            case 3:
                puts("Terima kasih"); 
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

int main(){ 
    menu(); 
    return 0; 
}