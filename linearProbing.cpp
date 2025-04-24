#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

int hash(int n, char name[]){
    int result = 0; 
    for(int i=0; i<strlen(name); i++){ 
        result += name[i];
    }
    return result % n;
}
int insert(int n, char names[][10], char name[]){
    int index = hash(n, name); 
    
    if(strlen(names[index]) != 0){
        int orginal = index; 
        do{
            if(strlen(names[index]) == 0){
                strcpy(names[index], name); 
                return 1; 
            }
            index = (index + 1) % n;
        }while(orginal != index); 
        return -1; 
    }
    strcpy(names[index],name);   
    return 1; 

}
int main (){
    int n = 20; 
    char names[n][10];
    for(int i=0; i<n; i++){
        strcpy(names[i], ""); 
    }
    insert(n, names, "Andi");
    insert(n, names, "Budi");
    insert(n, names, "Tono");
    insert(n, names, "Juni");
    insert(n, names, "Ratu");
    insert(n, names, "Jelvis");
    insert(n, names, "Intan");
    for(int i=0; i<n; i++){
        printf("%d - %s\n", i, names[i]); 
    } 
    return 0; 
} 
