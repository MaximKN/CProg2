#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "treenode.h"
#include "test.h"

int main(){
	checkNewNode();
	checkNewBase();
	checkQuery();
	checkReqQuery();
	checkInsert();
	checkComparators();
}

void checkNewNode(){
	printf("%s\n", "Start test #1");
	TreeBase* tree = new_base(compareInt, freeNode, printInt);

	int a = 5;
	int b = 4;
	int c = 0;
	int d = 6;
	int f = -1;

	// Add root
	tree->base = new_node(&a);
	assert(tree->base->value == &a);

	// Add left and right sub trees
	tree->base->left = new_node(&b);
	tree->base->left->left = new_node(&c);
	tree->base->right = new_node(&d);
	assert(tree->base->left->value == &b);
	assert(tree->base->left->left->value == &c);
	assert(tree->base->right->value == &d);

	printTree(tree);

	// Replace value
	tree->base->left->left = new_node(&f);
	assert(tree->base->left->left->value == &f);

	printTree(tree);

	freeTree(tree);
	printf("%s\n", "Test #1 finished without errors\n");
}

void checkNewBase(){
	printf("%s\n", "Start test #2");
	TreeBase* tree = new_base(NULL, NULL, NULL);

	assert(tree != NULL);
	assert(tree->base == NULL);

	tree = new_base(compareInt, freeNode, printInt);

	assert(tree->comp != compareFloat);
	assert(tree->comp == compareInt);
	assert(tree->clean == freeNode);
	assert(tree->print == printInt);

	printTree(tree);
	freeTree(tree);
	printf("%s\n", "Test #2 finished without errors\n");
}

void checkQuery(){
	printf("%s\n", "Start test #3");
	TreeBase* tree = new_base(compareInt, freeNode, printInt);
	int i = 3;
	int j = 0;
	int k = -8;
	int f = 6;

	insert(tree, &i);
	insert(tree, &j);
	insert(tree, &k);

	assert(&i == query(tree, &i)->value);
	assert(&j == query(tree, &j)->value);
	assert(&k == query(tree, &k)->value);
	
	tree->base->left->left = new_node(&k);
	tree->base->right = new_node(&f);	

	assert(&f == query(tree, &f)->value);
	assert(&k == query(tree, &k)->value);

	printTree(tree);
	freeTree(tree);
	printf("%s\n", "Test #3 finished without errors\n");
}

void checkReqQuery(){
	printf("%s\n", "Start test #4");
	TreeBase* tree = new_base(compareInt, freeNode, printInt);
	int i = 4;
	int j = 0;
	int k = -7;
	int f = 9;

	insert(tree, &i);
	insert(tree, &j);
	insert(tree, &k);

	assert(&i == query(tree, &i)->value);
	assert(&j == query(tree, &j)->value);
	assert(&k == query(tree, &k)->value);
	
	tree->base->left->left = new_node(&k);
	tree->base->right = new_node(&f);	

	assert(&f == query(tree, &f)->value);
	assert(&k == query(tree, &k)->value);

	printTree(tree);
	freeTree(tree);

	printf("%s\n", "Test #4 finished without errors\n");
}

void checkInsert(){
	printf("%s\n", "Start test #5");
	TreeBase* tree = new_base(compareInt, freeNode, printInt);
	int i = 0;
	int j = -7;
	int k = -1;
	int f = 70;

	insert(tree, &i);
	insert(tree, &j);
	insert(tree, &k);
	insert(tree, &f);

	assert(tree->base->value == &i);
	assert(tree->base->left->value == &j);
	assert(tree->base->left->right->value == &k);
	assert(tree->base->right->value == &f);

	assert(&i == query(tree, &i)->value);
	assert(&j == query(tree, &j)->value);
	assert(&k == query(tree, &k)->value);
	assert(&f == query(tree, &f)->value);

	printTree(tree);
	freeTree(tree);

	printf("%s\n", "Test #5 finished without errors\n");
}

void checkComparators(){
	printf("%s\n", "Start test #6");
	int i = 0;
	int j = 50;
	int k = -2;

	float a = 0.0;
	float b = 33.3;
	float c = -7.9;

	char d = 'b';
	char e = 'c';
	char f = 'f';

	assert(compareInt(&i, &j) == -1);
	assert(compareInt(&j, &k) == 1);
	assert(compareInt(&j, &j) == 0);

	assert(compareFloat(&a, &b) == -1);
	assert(compareFloat(&b, &c) == 1);
	assert(compareFloat(&b, &b) == 0);

	assert(compareChar(&d, &e) == -1);
	assert(compareChar(&f, &e) == 1);
	assert(compareChar(&e, &e) == 0);

	printf("%s\n", "Test #6 finished without errors\n");
}