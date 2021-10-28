#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "bst.h"


void main() {

    tree *myTree = NULL;

    insereRecursivo(&myTree, 10);
    insereRecursivo(&myTree, 7);
    insereRecursivo(&myTree, 8);
    insereRecursivo(&myTree, 22);
    insereRecursivo(&myTree, 15);
    insereRecursivo(&myTree, 35);
    insereRecursivo(&myTree, 16);

    preOrdemIterativo(myTree);

    printf("%d\n", nivel(myTree, 16));
    printf("Pai: %d\n", retornaPai(myTree, 10));
}