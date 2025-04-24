#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

struct Node {
    char name[101]; 
    char nim[101]; 
    int age; 
    Node *next; 
}; 

Node * head = NULL; 
Node * tail = NULL; 

Node * createNode (const char *name, const char *nim, int age){
    Node *newNode =(Node*)malloc(sizeof(Node)); 
    strcpy(newNode->name, name); 
    strcpy(newNode->nim, nim); 
    newNode->age = age; 
    newNode->next = NULL; 

    return newNode; 
}

void pushHead(const char*name, const char *nim, int age){
    Node * newNode = createNode(name, nim, age); 

    if(head == NULL){
        head = tail = newNode; 
    } else {
        newNode->next = head; 
        head = newNode; 
    }
}

void pushTail(const char*name, const char *nim, int age){
    Node *newNode = createNode(name, nim, age); 

    if(head == NULL){
        head = tail = newNode; 
    } else {
        tail->next = newNode; 
        tail = newNode; 
    }
}

void pushMid(const char *name, const char *nim, int age){
    Node * newNode = createNode(name, nim, age); 

    if(head == NULL){
        head = tail = newNode; 
    } else if(strcmp(name, head->name) <0){
        pushHead(name, nim,age); 
    } else if(strcmp(name, tail->name) >0){
        pushTail(name, nim, age); 
    } else {
        Node * curr = head; 
        while(curr->next != NULL && strcmp(name, curr->next->name)>0){
            curr = curr->next;
        } 
        newNode->next = curr->next; 
        curr->next = newNode; 
        
    }

}

void display(){
    if(head == NULL){
        puts("Data Kosong"); 
    } else {
        Node *curr = head; 
        puts("Data Siswa: "); 
        while(curr != NULL){
            printf("Name: %s\n", curr->name); 
            printf("NIM: %s\n", curr->nim); 
            printf("Age: %d\n", curr->age); 
            puts("==================================="); 
            curr = curr->next; 
        }
    }
}

void popHead(){
    if(head == NULL){
        puts("Tidak ada data"); 
        return; 
    } else if(head == tail){
        free(head); 
        head = tail = NULL; 
    } else {
        Node * temp = head; 
        head = head->next;
        free(temp); 
        temp = NULL;
    }
}

void popTail(){
    if(head==NULL){
        puts("Tidak ada data "); 
        return; 
    } else if(head == tail){
        free(head); 
        head = tail = NULL; 
    } else {
        Node *temp = head; 
        
        while(temp->next != tail){
            temp = temp->next; 
        }
        tail = temp; 
        free(temp->next);
        temp->next = NULL; 
    }
}

void popMid(const char * name){
    if(head == NULL){
        puts("Tidak ada data"); 
        return; 
    } else if(head == tail){
        head = tail = NULL; 
    } else if(strcmp(name, head->name)==0){
        popHead(); 
    } else if(strcmp(name, tail->name)==0){
        popTail(); 
    } else {
        Node * temp = head; 

        while( temp->next != NULL && strcmp(name, temp->next->name)>=0){
            temp = temp->next; 
        }
        Node * curr = temp->next; 
        curr->next = temp->next; 
        free(temp); 
        temp = NULL; 
    }
}

void popAll(){
    while(head != NULL){
        popHead(); 
    }
}

void menu(){
    int opt; 
    do{
        puts("Push Menu: "); 
        puts("1. Push Head"); 
        puts("2. Push Tail"); 
        puts("3. Push MId"); 
        puts("0. Display"); 

        puts(""); 
        puts("Pop Menu: "); 
        puts("4. pop Head");
        puts("5. pop Tail");
        puts("6. pop Mid");
        puts("7. pop All");
        puts("0. Display"); 
        puts("8. Exit"); 
        printf(">> "); 
        scanf("%d", &opt); 
        getchar();

        switch(opt){
            case 1: 
                pushHead("Jelvis", "2702365190", 19); 
                pushHead("Jelena", "240205290", 19); 
                pushHead("Donney", "2712331190", 21); 
                pushHead("Ashley", "271231240", 22); 
                pushHead("Kelvin", "27012341290", 19);
                break; 

            case 2: 
                pushTail("Jelvis", "2702365190", 19); 
                pushTail("Jelena", "240205290", 19); 
                pushTail("Donney", "2712331190", 21); 
                pushTail("Ashley", "271231240", 22); 
                pushTail("Kelvin", "27012341290", 19); 
                system("pause"); 
                break; 

            case 3: 
                pushMid("Jelvis", "2702365190", 19); 
                pushMid("Jelena", "240205290", 19); 
                pushMid("Donney", "2712331190", 21); 
                pushMid("Ashley", "271231240", 22); 
                pushMid("Kelvin", "27012341290", 19); 
                system("pause"); 
                break;

            case 0: 
                display(); 
                system("pause"); 
                break; 

            case 5: 
                popHead(); 
                break; 


            case 6: 
                popTail(); 
                break; 


            case 7: 
                char nameSearch[101]; 
                printf("Input name to delete: "); 
                scanf("%[^\n]", &nameSearch); 
                getchar(); 

                popMid(nameSearch);

            case 8: 
                popAll(); 
        
            case 9: 
                puts("Terimakasih"); 
                break; 
            
            default: 
                puts("Invalid Input"); 
                break; 
        } 
    }while(opt != 8); 
}

int main (){
    menu(); 
    return 0; 
}