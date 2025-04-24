#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

struct Node{
    char name[101]; 
    char id[101]; 
    int queue; 
    Node * next; 
}; 

Node * front = NULL; 
Node * rear = NULL; 

Node *createNode (const char *name, const char *id, int queue){
    Node * newNode = (Node *)malloc(sizeof(Node)); 
    strcpy(newNode->name, name); 
    strcpy(newNode->id, id); 
    newNode->queue = queue; 
    newNode->next = NULL; 

    return newNode; 
}

void push(const char *name, const char *id, int queue ){
    Node *newNode = createNode(name, id, queue); 

    if (front == NULL){
        front = rear = newNode; 
    } else if(queue > front->queue){
        newNode->next = front; 
        front = newNode; 
    } else{
        Node * curr = front; 
        while(curr->next != NULL && curr->next->queue >= queue){
            curr = curr->next; 
        }
        newNode->next = curr->next; 
        curr->next = newNode; 
    }
}

void inputQueue(){
    char name[101]; 
    char id[101]; 
    int queue; 

    int word; 
    do{
        word =0; 
        printf("Input name: "); 
        scanf("%[^\n]", &name); 
        getchar();

        char * token = strtok(name, " "); 
        while(token != NULL){
            word++; 
            token = strtok(NULL, " "); 
        }
    }while(word !=2); 

    do{
        printf("Input id: "); 
        scanf("%s", &id); 
        getchar();
    } while(strlen(id) < 3); 
    
    do{
        printf("Input queue level[0 --> Normal, 1--> VIP, 2--> VVIP]: "); 
        scanf("%d", &queue); 
        getchar();
    } while(queue !=0 && queue != 1 && queue!=2); 

    push(name, id, queue); 
}

void display(){
    if(front == NULL){
        puts("Belum ada antrian"); 
        return; 
    } else{
        int i = 0; 
        Node * curr = front; 
        puts("HAIDILAO QUEUE LIST"); 
        while(curr != NULL){
            i++; 
            printf("%d. %s %s %d\n", i, curr->name, curr->id, curr->queue); 
            curr = curr->next; 
        }
    }
}

void pop(){
    display(); 
    system("pause"); 
    
    if(front == NULL){
        puts("tidak ada antrian"); 
        return; 
    } else if(front == rear){
        free(front); 
        front = rear = NULL; 
    } else{
        Node * temp = front; 

        front = temp->next; 
        free(temp); 
        temp = NULL;
    }
}

void mainMenu(){
    int opt; 
    do{
        puts("HAIDILAO QUEUE"); 
        puts("=========================="); 
        puts("1. Input Queue"); 
        puts("2. Cancel Queue"); 
        puts("3. EXIT"); 
        puts("0. Display Queue"); 
        printf(">> "); 
        scanf("%d", &opt); 
        getchar(); 

        system("cls"); 
        switch(opt){
            case 1: 
                inputQueue(); 
                break; 

            case 2: 
                pop(); 
                break; 
            case 0: 
                display(); 
                system("pause"); 
                break; 

            case 3: 
                puts("Terimakasih");
                system("pause");
                break; 
            default: 
            puts("Invalid Input"); 
            system("pause"); 
            break; 
        }
    }while(opt !=3); 
}

int main(){
    mainMenu(); 
    return 0; 
}