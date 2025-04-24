#include <stdio.h>
#include <string.h> 

struct Minuman{
	int n; 
	char name[101]; 
}; 

Minuman minumanList[101]; 
int index = 1; 

int getParent(int childIndex){
	return childIndex / 2; 
}

int getLeftChild(int parentIndex){
	int child = 2*parentIndex; 
	
	if(child >= index) return 0; 
	return child; 
}

int getRightChild(int parentIndex){
	int child = 2*parentIndex +1; 

	if(child >= index) return 0; 
	return child; 
}

void swap(Minuman *a, Minuman *b){
	Minuman temp = *a; 
	*a = *b; 
	*b = temp; 
}

void insert(int n, char *name) {
    int indexToCheck = index;
    minumanList[indexToCheck].n = n;
    strcpy(minumanList[indexToCheck].name, name);
    index++;

    int parent = getParent(indexToCheck);

    while (parent != 0) {
        if (minumanList[indexToCheck].n <= minumanList[parent].n)
            break;

        swap(&minumanList[indexToCheck], &minumanList[parent]);
        indexToCheck = parent;
        parent = getParent(indexToCheck);
    }
}

void printHeap(){
	puts("Top Sales: "); 
	for(int i=1; i<3; i++){
		printf("%d. %s %d\n", i, minumanList[i].name, minumanList[i].n); 
	}
}


int main(){
	int t; 
    scanf("%d", &t); 
    getchar(); 

    for (int i = 1; i <= t; i++) {
        int n; 
        char name[101]; 
        scanf("%d %s", &n, name); 
        getchar();

		if(strcmp(name, "BC") == 0){
			strcpy(name, "Boba Coffee");  
		}

		if(strcmp(name, "MC") == 0){
			strcpy(name, "Moccapucino");  
		}
		
		if(strcmp(name, "PC") == 0){
			strcpy(name, "Pandan Coffee");  
		}
		
		if(strcmp(name, "BT") == 0){
			strcpy(name, "Boba Thai");  
		}

		if(strcmp(name, "CP") == 0){
			strcpy(name, "Choco Pandan");  
		}

		if(strcmp(name, "CC") == 0){
			strcpy(name, "Cheese Choco");  
		}
		
        int flag = 0;
        for (int j = 1; j < index; j++) {
            if (strcmp(name, minumanList[j].name) == 0) {
                minumanList[j].n += n; 
				int indexToCheck = j;
				int parent = getParent(indexToCheck);

				while (parent != 0) {
					if (minumanList[indexToCheck].n <= minumanList[parent].n)
						break;

					swap(&minumanList[indexToCheck], &minumanList[parent]);
					indexToCheck = parent;
					parent = getParent(indexToCheck);
				}
                flag = 1;
                break; 
            }
        }
        if (!flag) {
            insert(n, name); 
        }
    }
	printHeap(); 
	return 0; 
}
