#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "treenode.h"

//		-- Constructors --
TreeNode* new_node(void* data) { 
	TreeNode* treeNode = malloc(sizeof(TreeNode)); 
	treeNode->value = data; 
	treeNode->left = NULL;
	treeNode->right = NULL;

	return treeNode; 
} 
TreeBase* new_base(comp_fn co, clean_fn cl, print_fn p){
	TreeBase* treeBase = malloc(sizeof(TreeBase));
	treeBase->base = NULL;
	treeBase->comp = co;
	treeBase->clean = cl;
	treeBase->print = p;

	return treeBase;
}

//		-- Lookup --
TreeNode* query(TreeBase* tree, void* value){
	TreeNode* treeNode = tree->base;	// take a root node
	while(true){						// traverse the tree
		if (treeNode == NULL) return NULL;
		int comp_result = tree->comp(value, treeNode->value);
		if (comp_result == 0) return treeNode;
		else if (comp_result < 0) treeNode = treeNode->left;
		else treeNode = treeNode->right;
	}
}
TreeNode* reqQuery(TreeNode* treeNode, comp_fn comp, void* value){
	if (treeNode == NULL) return NULL;
	int comp_result = comp(value, treeNode->value);
	if (comp_result == 0) return treeNode;
	else if (comp_result < 0) return reqQuery(treeNode->left, comp, value);
	else return reqQuery(treeNode->right, comp, value);
}

//		-- Insertion --
void insert(TreeBase* tree, void* data){
	if (tree->base == NULL) tree->base = new_node(data);	// If the tree is empty create a node
	else{													 
		TreeNode* treeNode = tree->base;					
		while(true){
			int result = tree->comp(data, treeNode->value);
			if (result == -1){	// If value in current node 
				if (treeNode->left == NULL) {				// is greater than the given 
					treeNode->left = new_node(data);		// then go to the left sub tree
					return;
				}
				else treeNode = treeNode->left;
			}
		    else if (result == 1) {							// Otherwise, to the right
				if (treeNode->right == NULL) {
					treeNode->right = new_node(data);
					return;
				}
				else treeNode = treeNode->right;
			}
			else {
				return;
			}
		}
	}
}

// 		-- Comparators --
int compareInt(void* given_value, void* current_value){
	if (*(int*) given_value == *(int*) current_value) return 0;
	if (*(int*) given_value > *(int*) current_value) return 1;
	return -1;
}

int compareChar(void* given_value, void* current_value){
	if (*(char*) given_value == *(char*) current_value) return 0;
	if (*(char*) given_value > *(char*) current_value) return 1;
	return -1;
}

int compareFloat(void* given_value, void* current_value){
	if (*(float*) given_value == *(float*) current_value) return 0;
	if (*(float*) given_value > *(float*) current_value) return 1;
	return -1;
}

//		-- Cleaners --
void freeTree(TreeBase* tree){
	reqFreeTree(tree->base, tree->clean);
}
void reqFreeTree(TreeNode* treeNode, clean_fn clean){
	if (treeNode == NULL) return;
	reqFreeTree(treeNode->left, clean);
	reqFreeTree(treeNode->right, clean);
	clean(treeNode);
}
void freeNode(void* treeNode){
	free(treeNode);
}

//		-- Printers --
void printInt(void* i){
	printf("%d ", *((int*)i));
}
void printFloat(void* f){
	printf("%f\n", *((float*)f));
}
void printChar(void* c){
	printf("%c\n", *((char*)c));
}
void printTree(TreeBase* tree){
	reqInOrderPrintTree(tree->base, tree->print);
	printf("\n");
}
void reqInOrderPrintTree(TreeNode* treeNode, print_fn print){
	if (treeNode == NULL) return;
	reqInOrderPrintTree(treeNode->left, print);
	print(treeNode->value);
	reqInOrderPrintTree(treeNode->right, print);
}
