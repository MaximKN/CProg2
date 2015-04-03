#ifndef TREENODE_H
#define TREENODE_H

typedef struct TreeNodeName
{
    void* value;
    struct TreeNodeName* left;
    struct TreeNodeName* right;
} TreeNode;

typedef int(*comp_fn)(void*, void*);
typedef void(*clean_fn)(void*);
typedef void(*print_fn)(void*);

typedef struct
{
	TreeNode* base;
  comp_fn comp;
  clean_fn clean;
  print_fn print;
} TreeBase;

// Construct a new node 
TreeNode* new_node(void* data);

// Construct a new tree (which takes a comparison, print and clean method)
TreeBase* new_base(comp_fn co, clean_fn cl, print_fn p);

// Look a value up in the tree - return NULL when comp finds no node equal to 'value'
TreeNode* query(TreeBase* tree, void* value);

// Recursive implementaition of lookup function
TreeNode* reqQuery(TreeNode* treeNode, comp_fn comp, void* value);

// Compare specific type
int compareInt(void* given_value, void* current_value);
int compareFloat(void* given_value, void* current_value);
int compareChar(void* given_value, void* current_value);

// Add a value to the tree (this assumes the value is not already present).
void insert(TreeBase* tree, void* data);

// Print a tree (from smallest to largest member, using the print function). 
void printTree(TreeBase* tree);

// Reqursive implementaition of the print tree
void reqInOrderPrintTree(TreeNode* treeNode, print_fn print);

// Print specific type
void printInt(void* i);
void printFloat(void* f);
void printChar(void* c);

// Free all memory from a tree (using the 'clean' function on each 'value')
void freeTree(TreeBase* tree);

// Recursive implementaition of print tree
void reqFreeTree(TreeNode* treeNode, clean_fn clean);

// Clears the given node 
void freeNode(void* treeNode);

#endif

