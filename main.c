#include "./arvoreB.h"

void print_menu(void) {
  printf("\n\t+----+-----------------------------------+\n"
         "\t|  0 |               exit                |\n"
         "\t|  1 | inserir valores                   |\n"
         "\t|  2 | print inOrder                     |\n"
         "\t|  3 | print preOrder                    |\n"
         "\t|  4 | print posOrder                    |\n"
         "\t|  5 | remover valor                     |\n"
         "\t|  6 | contar nos                        |\n"
         "\t|  7 | contar nos nao-folha              |\n"
         "\t|  8 | altura da arvore                  |\n"
         "\t|  9 | soma dos valores                  |\n"
         "\t| 10 | media dos valores                 |\n"
         "\t| 11 | arvore esta balanceada?           |\n"
         "\t| 12 | arvore e estritamente binaria?    |\n"
         "\t| 13 | contar nos com um unico filho     |\n"
         "\t| 14 | criar vetor com valores da arvore |\n"
         "\t| 15 | imprimir vetor com valores        |\n"
         "\t| 16 | liberar arvore                    |\n"
         "\t+----+-----------------------------------+\n"
         "\t        Escolha: ");
}

int main() {
  TREE *tree = NULL;
  CONTAINER *container = NULL;
  container = criaContainer();
  tree = criaArvore();
  int escolha, aux;
  printf("\n\t+---+------+\n"
         "\t| 0 | menu |\n"
         "\t+---+------+\n"
         "\t| 1 | demo |\n"
         "\t+---+------+\n"
         "\t  Escolha: ");
  scanf("%i", &escolha);

  switch (escolha) {
  case 0:
    do {
      print_menu();
      scanf("%i", &escolha);
      switch (escolha) {
      case 1:
        printf("Value to insert in tree: ");
        scanf("%i", &aux);
        printf("\nInsert status: %s",
               error_descriptions[insercao_arvore(aux, tree)]);
        break;
      case 2:
        printf("\n in-order: ");
        in_ordem(tree->raiz);
        break;
      case 3:
        printf("\n pre-order: ");
        pre_ordem(tree->raiz);
        break;
      case 4:
        printf("\n pos-order: ");
        pos_ordem(tree->raiz);
        break;
      case 5:
        printf("Value to remove from the tree: ");
        scanf("%i", &aux);
        printf("\nRemoval status: %s", error_descriptions[remover(aux, tree)]);
        break;
      case 6:
        printf("\nNumber of NODES in the tree is : %i\n", nodeQuantity(tree->raiz));
        break;
      case 7:
        printf("\nNumber of PARENT NODES in the tree is : %i\n",
           parentsInTree(tree->raiz));
        break;
      case 8:
        printf("\nHeight of the tree is: %i\n", binaryTreeHeight(tree->raiz));
        break;
      case 9:
        printf("\nSum of values in the tree is: %i\n", binaryTreeSum(tree->raiz));
        break;
      case 10:
        printf("\nAverage of values in the tree is: %.3f\n",
           binaryTreeAverage(tree->raiz));
        break;
      case 11:
        printf("\n%s\n", isBalanced(tree->raiz) ? "The tree is balanced" : "the three is NOT balanced");
        break;
      case 12:
        printf("\n%s\n", isStrictlyBinary(tree->raiz) ? "The tree is strictly binary" : "the three is NOT strictly binary");
        break;
      case 13:
        printf("\nNumber of SINGLE CHILD PARENT node in the tree is : %i\n",
           singleChildParents(tree->raiz));
        break;
      case 14:
        container->sizeOfArr = 0;
        free(container->arr);
        container = criaContainer();
        printf("Number you want the values to be lower than: ");
        scanf("%i", &aux);
        lowerThanToArr(tree->raiz, aux, container);
        break;
      case 15:
        printfArr(container);
        break;
      case 16:
        free_tree(tree);
        printf("\nTree deleted");
        break;
      case 0:
        free_tree(tree);
        printf("\nbyeee \t -Ana Atala\n");
        break;
      default:
        printf("\nOpcao invalida");
        break;
      }
    } while (escolha != 0);
    free_tree(tree);
    break;
  case 1:
    printf("\n\nis tree empty? %s\n", isEmpty(tree) ? "yes" : "no");
    printf("\nInsert status: %s",
           error_descriptions[insercao_arvore(15, tree)]);
    printf("\nInsert status: %s",
           error_descriptions[insercao_arvore(30, tree)]);
    printf("\nInsert status: %s", error_descriptions[insercao_arvore(7, tree)]);
    printf("\nInsert status: %s",
           error_descriptions[insercao_arvore(40, tree)]);
    printf("\nInsert status: %s",
           error_descriptions[insercao_arvore(20, tree)]);
    printf("\nInsert status: %s",
           error_descriptions[insercao_arvore(10, tree)]);
    printf("\nInsert status: %s", error_descriptions[insercao_arvore(4, tree)]);
    printf("\nInsert status: %s", error_descriptions[insercao_arvore(0, tree)]);

    printf("\n\n");
    printf("In order:\t");
    in_ordem(tree->raiz);
    printf("\n\nis tree empty? %s\n", isEmpty(tree) ? "yes" : "no");
    printf("\nHeight of the tree is: %i\n", binaryTreeHeight(tree->raiz));
    printf("\nNumber of NODES in the tree is : %i\n", nodeQuantity(tree->raiz));
    printf("\nNumber of PARENT NODES in the tree is : %i\n",
           parentsInTree(tree->raiz));
    printf("\nSum of values in the tree is: %i\n", binaryTreeSum(tree->raiz));
    printf("\nAverage of values in the tree is: %.3f\n",
           binaryTreeAverage(tree->raiz));
    printf("\nis tree balanced? %s\n", isBalanced(tree->raiz) ? "yes" : "no");
    printf("\nNumber of SINGLE CHILD PARENT node in the tree is : %i\n",
           singleChildParents(tree->raiz));
    printf("\nis Tree strictly balanced? %s\n",
           isStrictlyBinary(tree->raiz) ? "yes" : "no");

    lowerThanToArr(tree->raiz, 14, container);
    printfArr(container);

    free_tree(tree);
    printf("\n\nis tree empty? %s\n", isEmpty(tree) ? "yes" : "no");
    break;
  default:
    printf("\nbye");
    break;
  }

  return 0;
}