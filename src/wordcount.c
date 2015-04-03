#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "treenode.h"
#include "wordcount.h"
#define BUFFER_SIZE 20
int main(){
	FILE *fp;
	char c, file_name[sizeof(char)], oneword[sizeof(char)];
	TreeBase* tree = new_base(compareWords, freeNode, printWordCount);

   	printf("Enter the name of file you wish to see\n> ");
    scanf("%s", file_name);
    fp = fopen(file_name,"r");

	// Check error
    if (fp == NULL){
    	perror("Error while opening the file.\n");
      	exit(EXIT_FAILURE);
    }
    int i = 0;
	// Read the whole file
    while ((c = fgetc(fp)) != EOF){ 	// get charachters from the file until the end		
    	// if in is not alphanumeric
      	if (!((c >= 'a' && c <= 'z') || ((c >= 'A' && c <= 'Z') || c == '\0'|| c == '\''))){  
      		oneword[i] = '\0'; 	// end of the string
		    if (strlen(oneword) > 0){	// Word cannot be empty
	      		WordCount* wc = new_word(oneword);
		    	insert(tree, wc);
		    	i = 0; 
		    }
	    }
	    else{
		    c = tolower(c); // convert all letters in the word to lowercase	
			oneword[i] = c;
			i++;
		}
    }

    fclose(fp);
    printTree(tree);

    int max = maxCount(tree->base); // find most common word counter

    printf("The most common word \"%s\" occurs %d times\n", mostUsedWord(tree->base, max), max);
    printf("Total number of characters in all words: %d\n", sumWordLength(tree->base));
    printf("Average word length: %d\n", averageWordLength(tree->base));
    printf("Total number of words: %d", totalNumOfWords(tree->base));
    freeTree(tree);
}

WordCount* new_word(char* oneword){
	WordCount* treeBase = malloc(sizeof(WordCount));
	char* dupicate = malloc(sizeof(oneword)*BUFFER_SIZE); // allocate more memory for the word
	memcpy(dupicate, oneword, strlen(oneword)+1);  // copy memory to duplicate node
	treeBase->word = dupicate;
	treeBase->count = 1;
	return treeBase;
}

int compareWords(void* given_value, void* current_value){
	int result = strcmp(((WordCount*)given_value)->word, 
						((WordCount*)current_value)->word);
	if (result == 0) {
		((WordCount*)current_value)->count++;
		return 0;
	}
	else if (result > 0) return 1;
	else return -1;
}

void printWordCount(void* wc){
	printf("(%s,%d)\n", ((WordCount*)wc)->word, ((WordCount*)wc)->count);
}

int totalNumOfWords(TreeNode* treeNode){
	if (treeNode == NULL) return 0;
	return totalNumOfWords(treeNode->left) + 
		   ((WordCount*)treeNode->value)->count + 
		   totalNumOfWords(treeNode->right);
}

int sumWordLength(TreeNode* treeNode){
	if (treeNode == NULL) return 0;
	return sumWordLength(treeNode->left) + 
		   strlen(((WordCount*)treeNode->value)->word) * 
		   		  ((WordCount*)treeNode->value)->count + 
		   sumWordLength(treeNode->right);
}

int averageWordLength(TreeNode* treeNode){
	return sumWordLength(treeNode) / totalNumOfWords(treeNode);
}

int maxCount(TreeNode* treeNode){
	if (treeNode == NULL) return -1;
	int left = maxCount(treeNode->left);
	int right = maxCount(treeNode->right);
	
	// Find max of counters
	if (((WordCount*)treeNode->value)->count >= left && 
		((WordCount*)treeNode->value)->count >= right)
        return ((WordCount*)treeNode->value)->count;
    else if (left >= ((WordCount*)treeNode->value)->count && left >= right)
        return left;
    else
        return right;
}

char* mostUsedWord(TreeNode* treeNode, int maxCount){
	if (treeNode != NULL){
		if (((WordCount*)treeNode->value)->count == maxCount)
			return ((WordCount*)treeNode->value)->word;

		char* leftTree = mostUsedWord(treeNode->left, maxCount);
		char* rightTree = mostUsedWord(treeNode->right, maxCount);

		// If it not null means that it found a word.
		if (leftTree != NULL)
			return leftTree;
		if (rightTree != NULL)
			return rightTree;
		else return NULL;
	} else return NULL;
}






