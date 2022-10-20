#include "./arvoreB.h"

/*Print functions that came from the first code project*/
void in_ordem(NO *pt) {
  if (pt == NULL){
    printf("nothing here");
    return;
  }
  
  if (pt->esq != NULL) {
    in_ordem(pt->esq);
  }
  printf("%d ", pt->chave);
  if (pt->dir != NULL) {
    in_ordem(pt->dir);
  }
}

void pre_ordem(NO *pt) {
  if (pt == NULL){
    printf("nothing here");
    return;
  }
  
  printf("%d ", pt->chave);
  if (pt->esq != NULL) {
    pre_ordem(pt->esq);
  }
  if (pt->dir != NULL) {
    pre_ordem(pt->dir);
  }
}

void pos_ordem(NO *pt) {
  if (pt == NULL){
      printf("nothing here");
      return;
    }
  
  if (pt->esq != NULL) {
    pos_ordem(pt->esq);
  }
  if (pt->dir != NULL) {
    pos_ordem(pt->dir);
  }
  printf("%d ", pt->chave);
}

/*function to create a Tree structure pointer*/
TREE *criaArvore(void) {
  TREE* t = (TREE *)malloc(sizeof(TREE));
  if (t == NULL) {
    printf("\nComprar Memoria.\n");
    exit(1);
  }
  t->raiz = NULL;
  return t;
}

/*Function to create the struct pointer for the vector*/
CONTAINER* criaContainer(void){
  CONTAINER* c = (CONTAINER* )malloc(sizeof(CONTAINER));
  if(c == NULL){
    printf("\nComprar Memoria.\n");
    exit(1);
  }
  c->sizeOfArr = 0;
  c->arr = (int*)malloc(sizeof(CONTAINER)*0);
  return c;
}

/*Boolean function answers the question "is the tree empty?"*/
boolean isEmpty(TREE *tree){
  if (tree == NULL){
    return True;
  }
  if (tree->raiz == NULL){
    return True;
  }
  return False;
}

/*Recursive function to search a value or the place to insert a new value*/
NO* busca_arvore(int x, NO *pt) {
  /* tree is empty */
  if (pt == NULL){
    return NULL; 
  }

  /* Value already exists in the tree */
  if (x == pt->chave){
    return pt; 
  }

  /* Value to be inserted is lower than current value, work on the left side of the tree*/
  if (x < pt->chave){

    /* subTree to the left is empty, found the place to insert new value*/
    if (pt->esq == NULL) {
      return pt;
    }
    // subTree is not empty, will continue to look for a place to insert the new value.
    return busca_arvore(x, pt->esq);
  }

  // if value is not lower, then it must be higher
  if (pt->dir == NULL){
    // subTree to the right is empty, found the place to insert new value
    return pt;
  }
  // subTree to the right is not empty, will continue to look for a place to insert the new value
  return busca_arvore(x, pt->dir); 
}

/*Insert function*/
statusCode insercao_arvore(int x, TREE *tree) {
  NO *pt = busca_arvore(x, tree->raiz);

  /*won't insert value if it is already present in the tree*/
  if (pt != NULL && pt->chave == x) {
    return VALUE_ALREADY_EXISTS;
  }

  NO *novo = (NO *)malloc(sizeof(NO));
  if (novo == NULL) {
    printf("\nComprar Memoria.\n");
    exit(1);
  }
  novo->chave = x;
  novo->esq = NULL;
  novo->dir = NULL;
  novo->pai = pt;

  if (pt == NULL) {
    tree->raiz = novo;
  } else if (x < pt->chave) {
    pt->esq = novo;
  } else {
    pt->dir = novo;
  }

  return SUCCESSFUL_INSERT;
}

/*Function to remove a value from the tree*/
statusCode remover(int chave, TREE *tree) {
  NO *pt = busca_arvore(chave, tree->raiz);

  /*Value not found, nothing changed*/
  if (pt == NULL){
    return NOT_FOUND;
  }

  /*Value is a leaf*/
  if (pt->esq == NULL && pt->dir == NULL){
    /* need to find it's placement in relation to it's father */
    if (pt->chave > pt->pai->chave){
      pt->pai->dir = NULL;
    }else{
      pt->pai->esq = NULL;
    }
    free(pt);
    return SUCCESSFUL_REMOVAL;    
  }

  /*Value has children to the right*/
  if (pt->dir != NULL && pt->esq == NULL){
    /*points parent to the child of the node*/
    if (pt-> chave > pt->pai->chave){
      pt->pai->dir = pt->dir;
    }else{
      pt->pai->esq = pt->dir;
    }
    //correctly correlates the children to the grandparent
    pt->dir->pai = pt->pai;
    free(pt);
    return SUCCESSFUL_REMOVAL;
  }

  /*Value has children to the left*/
  if (pt->esq != NULL && pt->dir == NULL){
    /*points parent to the child of the node*/
    if (pt-> chave > pt->pai->chave){
      pt->pai->dir = pt->esq;
    }else{
      pt->pai->esq = pt->esq;
    }
    //correctly correlates the children to the grandparent
    pt->esq->pai = pt->pai;
    free(pt);
    return SUCCESSFUL_REMOVAL;
  }

  /*Value is an internal node */
  if (pt->dir != NULL && pt->esq != NULL){
    NO *aux = pt->esq;
    while (aux->dir != NULL) {
      aux = aux->dir;
    }
    pt->chave = aux->chave;

    if (aux->esq != NULL){
      if (aux->chave > aux->pai->chave){
        aux->pai->dir = aux->esq;
      }else{
        aux->pai->esq = aux->esq;
      }
      aux->esq->pai = aux->pai;
    }
    free(aux);
    return SUCCESSFUL_REMOVAL;
  }
  return UNKNOWN_ERROR;
}

/*free tree from memory*/
void free_tree(TREE *tree){
  tree->raiz = free_nodes(tree->raiz);
  tree->raiz = NULL;
}

/*recursive function to delete the nodes*/
NO* free_nodes(NO *root){
  if(root != NULL){

    free_nodes(root->esq);
    free_nodes(root->dir);

    free(root);
  }
  return NULL;
}

/*recursive function that counts all the nodes of the tree*/
int nodeQuantity(NO* pt){
  int leftHeight = 0, rightHeight = 0;
  
  if (pt == NULL){
    return 0;
  }
  
  leftHeight = nodeQuantity(pt->esq);
  rightHeight = nodeQuantity(pt->dir);  

  return (leftHeight + rightHeight + 1);
}

/*recursive function that counts all the parents nodes of the tree*/
int parentsInTree(NO* pt){
  if (pt == NULL){
    return 0;
  }
  
  //excluding all leaves
  if (pt->esq == NULL && pt->dir == NULL){
    return 0;
  }
  
  return (1 + parentsInTree(pt->esq) + parentsInTree(pt->dir));
}

/*recursive function that returns the height of the tree*/
int binaryTreeHeight(NO* pt){
  int leftHeight = 0, rightHeight = 0;

  if (pt == NULL){
    return 0;
  }

  leftHeight = binaryTreeHeight(pt->esq);
  rightHeight = binaryTreeHeight(pt->dir);
  
  if (leftHeight > rightHeight){
    return (leftHeight +1);
  }
  return (rightHeight + 1);
}

/*recursive function that sums all the values of the tree*/
int binaryTreeSum(NO* pt){
  if (pt == NULL){
    return 0;
  }

  return (pt->chave + binaryTreeSum(pt->esq) + binaryTreeSum(pt->dir));
}

/*recursive function that returns the numbers of nodes with only one child*/
int singleChildParents(NO* pt){
  int leftSideQuantity = 0, rightSideQuantity = 0;
  
  if (pt == NULL){
    return 0;
  }
  if (pt->esq != NULL && pt->dir == NULL){
    return (1 + singleChildParents(pt->esq));
  }
  if (pt->esq == NULL && pt->dir != NULL){
    return (1 + singleChildParents(pt->dir));
  }
  return (singleChildParents(pt->esq) + singleChildParents(pt->dir));
}

/*function that returns the average of the values of the tree*/
float binaryTreeAverage(NO* pt){
  int sumOfValues = binaryTreeSum(pt);
  int nQuantity = nodeQuantity(pt);

  //so a error wont occur if the tree is empty
  if (nQuantity == 0){
    return 0;
  }

  return (sumOfValues/(float)nQuantity);
}

/*recursive function that answers the question "is the tree balanced?"*/
boolean isBalanced(NO* pt){
  int leftHeight = 0, rightHeight = 0;

  if(pt == NULL){
    return 1;
  }

  leftHeight = binaryTreeHeight(pt->esq);
  rightHeight = binaryTreeHeight(pt->dir);
  

  if (abs(leftHeight - rightHeight) <= 1 && isBalanced(pt->esq) && isBalanced(pt->dir)){
    return 1;
  }

  return 0;
}

/*recursive functions that answers the question "is the tree strictly binary?"*/
boolean isStrictlyBinary(NO* pt){
  if (pt == NULL){
    return 1;
  }

  if (pt->esq != NULL && pt->dir == NULL){
    return 0;
  }
  if (pt->esq == NULL && pt->dir != NULL){
    return 0;
  }

  return (isStrictlyBinary(pt->esq) && isStrictlyBinary(pt->dir));
}

/*recursive function that will add values to vector*/
void lowerThanToArr(NO* pt, int threshold, CONTAINER* container){
  if (pt == NULL){
    return NULL;
  }
  
  if (pt->chave < threshold){
    container->arr = (int*)realloc(container->arr, container->sizeOfArr + 1);
    container->arr[container->sizeOfArr++] = pt->chave;
    lowerThanToArr(pt->esq, threshold, container);
    lowerThanToArr(pt->dir, threshold, container);
  }else{
    lowerThanToArr(pt->esq, threshold, container);
  }
}

/*function to print the array*/
void printfArr(CONTAINER* container){
  int i = 0;

  if(container->sizeOfArr == 0){
    printf("\narray is empty!\n");
  }

  for(i = 0; i < container->sizeOfArr; i++){
    printf("\n\tvet[%i]: %i", i, container->arr[i]);
  }
  printf("\n");
}