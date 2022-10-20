#ifndef arvoreB_Atala
#define arvoreB_Atala

// libraries
#include <stdio.h>
#include <stdlib.h>

// discounted booleans
typedef enum { False = 0, True = 1 } boolean;

// discounted error codes
typedef enum {
  SUCCESSFUL_REMOVAL = 0,
  SUCCESSFUL_INSERT,
  SUCCESSFUL_TREE_SORT,
  VALUE_ALREADY_EXISTS,
  NOT_FOUND,
  TREE_IS_EMPTY,
  UNKNOWN_ERROR,
  TREE_IS_BALANCED,
  TREE_IS_NOT_BALANCED,
} statusCode;

static const char * error_descriptions[] = {
  [SUCCESSFUL_REMOVAL] = "Value was removed from the Tree successfully.",
  [SUCCESSFUL_INSERT] = "Value was inserted in the Tree successfully.",
  [SUCCESSFUL_TREE_SORT] = "Tree was sorted successfully",
  [NOT_FOUND] = "Value wasn't present on the Tree.",
  [VALUE_ALREADY_EXISTS] = "Value already exists in the Tree.",
  [TREE_IS_EMPTY] = "Tree is empty and all is void.",
  [UNKNOWN_ERROR] = "Something happened. Report this bug to Ana Atala.",
  [TREE_IS_BALANCED] = "Tree is Balanced",
  [TREE_IS_NOT_BALANCED] = "Tree is NOT Balanced",
};

// structs
typedef struct no {
  int chave;
  struct no *pai;
  struct no *esq;
  struct no *dir;
} NO;

typedef struct tree {
  struct no *raiz;
} TREE;

typedef struct container{
  int *arr;
  int sizeOfArr;
} CONTAINER;

// funcions

/*Prints binary tree in order*/
void in_ordem(NO *pt);

/*Prints binary tree in pre order*/
void pre_ordem(NO *pt);

/*Prints binary tree post order*/
void pos_ordem(NO *pt);

/*returns true if the tree is empty*/
boolean isEmpty(TREE *tree);

/*Searches the binary tree and returns the node if found, or null if not*/
NO *busca_arvore(int x, NO *pt);

/*Create tree*/
TREE *criaArvore(void);

CONTAINER* criaContainer(void);

void lowerThanToArr(NO* pt, int threshold, CONTAINER* container);

/*function to print the vector*/
void printfArr(CONTAINER* container);

/*Inserts data in the binary tree*/
statusCode insercao_arvore(int x, TREE *tree);

/*Removes a node from the tree*/
statusCode remover(int chave, TREE *tree);

/*erases all values in the tree*/
void free_tree(TREE *tree);

/*will free the nodes from the tree from memory*/
NO* free_nodes(NO *root);

/*will return the quantity of all nodes in the tree (leaves included)*/
int nodeQuantity(NO* pt);

/*will return the quantity of parent nodes only (leaves excluded)*/
int parentsInTree(NO* pt);

/*will return the height of the tree*/
int binaryTreeHeight(NO* pt);

/*will return the sum of all the values in the tree*/
int binaryTreeSum(NO* pt);

/*will return the average of values in the tree*/
float binaryTreeAverage(NO* pt);

/*will return if the tree is balanced or not*/
boolean isBalanced(NO* pt);

/*will return true if the tree is a strictly binary tree*/
boolean isStrictlyBinary(NO* pt);

/*will return the numbewr of nodes with a single child*/
int singleChildParents(NO* pt);

#endif