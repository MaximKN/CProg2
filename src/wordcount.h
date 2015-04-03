#ifndef WORDCOUNT_H
#define WORDCOUNT_H

typedef struct WordCount
{
    char* word;
    int count;
} WordCount;

int compareWords(void* given_value, void* current_value);
void printWordCount(void* wc);
int totalNumOfWords(TreeNode* treeNode);
int averageWordLength(TreeNode* treeNode);
int sumWordLength(TreeNode* treeNode);

// Finds maximum count value in the tree
int maxCount(TreeNode* treeNode);

// Finds most common word in the tree by comparing the given maximum count
char* mostUsedWord(TreeNode* treeNode, int maxCount);

// Construct a new word 
WordCount* new_word(char* oneword);

#endif