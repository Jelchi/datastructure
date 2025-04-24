#include <stdio.h>
#include <string.h>
#include <stdlib.h>



struct WordNode{
	char word[101]; 
	int height; 
	WordNode * left; 
	WordNode * right; 
};

struct LangNode{
	char lang[101];
	int height; 
	LangNode * left; 
	LangNode * right; 
	
	WordNode * wordnode;
	int count;  
};

LangNode * root = NULL; 

WordNode * createWord(char * word){
	WordNode * newWord = (WordNode*)malloc(sizeof(WordNode)); 
	strcpy(newWord->word, word); 
	newWord->height =1; 
	newWord->left = NULL; 
	newWord->right = NULL; 
	
	return newWord; 
}

LangNode * createLanguage(char * lang, char * word){
	LangNode * newLang = (LangNode*)malloc(sizeof(LangNode)); 
	strcpy(newLang->lang, lang); 
	newLang->height = 1; 
	newLang->left = NULL; 
	newLang->right = NULL; 
	
	newLang->wordnode = createWord(word); 
	newLang->count = 1; 
	
	return newLang; 
}


int findMax(int left, int right){
	if(left>right){
		return left; 
	} else {
		return right; 
	}
}

int getLangHeight(LangNode * root){
	if(root == NULL){
		return NULL; 
	} else{
		return root->height; 
	}
}

int getWordHeight(WordNode * root){
	if(root == NULL){
		return NULL; 
	} else {
		return root->height; 
	}
}

void updateLangHeight(LangNode * root){
	root->height = findMax(getLangHeight(root->left), getLangHeight(root->right))+1; 
}

void updateWordHeight(WordNode * root){
	root->height = findMax(getWordHeight(root->left), getWordHeight(root->right))+1; 
}

int langBF(LangNode * root){
	if(root == NULL){
		return NULL; 
	} else {
		return getLangHeight(root->left)-getLangHeight(root->right); 
	}
}

int wordBF(WordNode * root){
	if(root == NULL){
		return NULL; 
	} else {
		return getWordHeight(root->left)-getWordHeight(root->right); 
	}
}

LangNode * langRightRotate(LangNode * root){
	LangNode * left = root->left; 
	LangNode * leftRight = left->right; 
	
	left->right = root; 
	root->left = leftRight; 
	
	updateLangHeight(root); 
	updateLangHeight(left); 
	
	return left; 
}

LangNode * langLeftRotate(LangNode * root){
	LangNode * right = root->right; 
	LangNode * rightLeft = right->left; 
	
	right->left = root; 
	root->right = rightLeft; 
	
	updateLangHeight(root); 
	updateLangHeight(right); 
	
	return right; 
} 

WordNode * wordRightRotate(WordNode * root){
	WordNode * left = root->left; 
	WordNode * leftRight = left->right; 
	
	left->right = root; 
	root->left = leftRight; 
	
	updateWordHeight(root); 
	updateWordHeight(left); 
	
	return left;
}

WordNode * wordLeftRotate(WordNode * root){
	WordNode * right = root->right; 
	WordNode * rightLeft = right->left; 
	
	right->left = root; 
	root->right = rightLeft; 
	
	updateWordHeight(root); 
	updateWordHeight(right); 
	
	return right; 
}

WordNode * balancingWord(WordNode * root){
	updateWordHeight(root); 
	int bf = wordBF(root); 
	
	if(bf>1){
		if(wordBF(root->left)>0){
			root = wordRightRotate(root);
		} else {
			root->left = wordLeftRotate(root->left); 
			root = wordRightRotate(root); 
		} 
	} else if(bf<-1){
		if(wordBF(root->right)<0){
			root = wordLeftRotate(root); 
		} else {
			root->right = wordRightRotate(root->right); 
			root = wordLeftRotate(root); 
		}
	}
	return root; 	
}

WordNode * wordInsert(WordNode * root, char*word){
	if(root == NULL){
		return createWord(word); 
	}
	if(strcmp(word, root->word)!= 0){
		if(strcmp(word, root->word) <0){
			root->left = wordInsert(root->left, word); 
		} else if(strcmp(word, root->word)>0){
			root->right = wordInsert(root->right, word); 
		} else {
			return root; 
		}
	}
	return balancingWord(root); 
}

LangNode * balancingLang(LangNode * root){
	updateLangHeight(root); 
	int bf = langBF(root); 
	
	if(bf>1){
		if(langBF(root->left)>0){
			root = langRightRotate(root);
		} else {
			root->left = langLeftRotate(root->left); 
			root = langRightRotate(root); 
		} 
	} else if(bf<-1){
		if(langBF(root->right)<0){
			root = langLeftRotate(root); 
		} else {
			root->right = langRightRotate(root->right); 
			root = langLeftRotate(root); 
		}
	}
	return root; 
}

LangNode * langInsert(LangNode * root, char *lang, char * word){
	if(root == NULL){
		return createLanguage(lang, word); 
	}
	if(strcmp(lang, root->lang) != 0){
		if(strcmp(lang, root->lang)<0){
			root->left = langInsert(root->left, lang, word); 
		} else if(strcmp(lang, root->lang)>0){
			root->right = langInsert(root->right, lang, word); 
		} else {
			return root; 
		}
	}else {
		root->count++; 
		root->wordnode = wordInsert(root->wordnode, word);  
	}
	return balancingLang(root); 
}

void displayWord(WordNode * root){
	if(root != NULL){
		displayWord(root->left); 
		printf("- %s\n", root->word); 
		displayWord(root->right); 
	}
}

void displayALL(LangNode * root){
	if(root != NULL){
		displayALL(root->left); 
		printf("%s (%d): \n", root->lang, root->count); 
		displayWord(root->wordnode); 
		displayALL(root->right); 
	}
}

LangNode * searchingLang(LangNode * root, char *lang){
	if(root != NULL){
		return NULL; 
	}
	
	if(strcmp(lang, root->lang)==0){
		return root; 
	} 
	
	if(strcmp(lang, root->lang) < 0){
		return searchingLang(root->left, lang); 
	}
	
	if(strcmp(lang, root->lang) > 0){
		return searchingLang(root->right, lang); 
	}
}

void displayLang(LangNode * root, char *lang){
	if(root != NULL){
		LangNode * result = searchingLang(root, lang); 
		
		if(result != NULL){
			printf("%s (%d): \n", result->lang, result->count); 
			displayWord(root->wordnode); 
		} else {
			printf("%s language not found\n", lang); 
		}
	}
}
LangNode * langPredecessor(LangNode* root) {
    root = root->left;
    while (root->right != NULL) {
        root = root->right;
    }
    return root;
}

WordNode * wordPredecessor(WordNode * root){
	root = root ->left; 
	while(root->right != NULL){
		root = root->right; 
	}
	return root; 
}

LangNode * delLang(LangNode * root, char * lang , int flag){
	if(root == NULL){
		printf("Language (%s) not found\b", lang); 
		return NULL; 
	}
	if(strcmp(lang, root->lang) < 0){
		root->left = delLang(root->left, lang, flag); 
	} else if(strcmp(lang, root->lang) > 0){
		root->right = delLang(root->right, lang, flag); 
	} else if(strcmp(lang, root->lang) == 0){
		if(flag == 0){
			puts("Successfully Deleted\n"); 
			flag = 1; 
		}
		
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL; 
		} else if(root->left == NULL){
			 LangNode * temp = root->right; 
			 free(root); 
			 root = temp; 
		} else if(root->right == NULL){
			LangNode * temp = root->left; 
			free(root); 
			root = temp; 
		} else {
			LangNode * temp = langPredecessor(root); 
			strcpy(root->lang, temp->lang); 
			root->count = temp->count; 
			*(root->wordnode) = *(temp->wordnode); 
			root->left =  delLang(root->left, temp->lang, 1); // delete the predecessor root
		}
		return root; 
	}
	return balancingLang(root); 
}

WordNode * delWord(WordNode * root, char * word, int flag, int *count){
	if(root == NULL){
		printf("Word (%s) not found\b", word); 
		return NULL; 
	}
	if(strcmp(word, root->word) < 0){
		root->left = delWord(root->left, word, flag, count); 
	} else if(strcmp(word, root->word) > 0){
		root->right = delWord(root->right, word, flag, count); 
	} else if(strcmp(word, root->word) == 0){
		if(flag == 0){
			puts("Successfully Deleted\n"); 
			flag = 1; 
			*count = -1; 
		}
		
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL; 
		} else if(root->left == NULL){
			 WordNode * temp = root->right; 
			 free(root); 
			 root = temp; 
		} else if(root->right == NULL){
			WordNode * temp = root->left; 
			free(root); 
			root = temp; 
		} else {
			WordNode * temp = wordPredecessor(root); 
			strcpy(root->word, temp->word); 
			root->left =  delWord(root->left, temp->word, 1, count); // delete the predecessor root
		}
		return root; 
	}
	return balancingWord(root); 
}

WordNode * freeAllWord(WordNode * root){
	if(root == NULL){
		return NULL; 
	} else{
		root->left = freeAllWord(root->left);
    	root->right = freeAllWord(root->right);
    	free(root);
    	return NULL;
	}
}

LangNode * freeAllLang(LangNode * root){
	if(root == NULL){
		return NULL; 
	} else{
		root->left = freeAllLang(root->left);
    	root->right = freeAllLang(root->right);
    	free(root);
    	return NULL;
	}
}

LangNode * searchDeleteWord(LangNode * root, char *lang, char *word){
	if(root == NULL){
		printf("Word (%s) not found\n", word); 
		return NULL; 
	}

	if(strcmp(lang, root->lang) < 0){
		return searchDeleteWord(root->left, lang, word); 
	}
	
	if(strcmp(lang, root->lang) > 0){
		searchDeleteWord(root->right, lang, word); 
	}
	
	if(strcmp(lang, root->lang)==0){
		int count = root->count; 
		root->wordnode = delWord(root->wordnode, word, 0, &count); 
		root->count = count; 
	} 
	
	
	return root; 
}

int main (){
	int t; 
	char operation[101]; 
	char lang[101]; 
	char word[101]; 
	
	scanf("%d", &t); 
	getchar(); 
	
	for(int i=0; i<t; i++){
		scanf("%s", &operation); 
		printf("Case %d: \n", i+1); 
		
		if(strcmp(operation, "ADD")==0){
			scanf("%s %s", lang, word); 
			
			root = langInsert(root , lang, word); 
			puts("Successfully Added"); 
		}
		
		if(strcmp(operation, "SHOW-ALL")==0){
			displayALL(root); 
		} 
		
		if(strcmp(operation, "SHOW-LANG")==0){
			scanf("%s", &lang); 
			displayLang(root, lang); 
		}
		
		if(strcmp(operation, "DEL-LANG")==0){
			scanf("%s", &lang);
			root = delLang(root, lang, 0); 
		}
		
		if (strcmp(operation, "DEL_WORD")==0){
			scanf("%s %s", lang, word); 
			root = searchDeleteWord(root, lang, word); 
		}
	}
	freeAllLang(root);
	return 0; 
}
