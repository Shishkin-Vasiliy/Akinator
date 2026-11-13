#include <stdio.h>
#include "Tree.h"

int main(void)
{
    Tree_t Tree = {};

    LogCtx_t LogCtx = {};
    TreeLogInit(&Tree, &LogCtx);

    PreOrderCtor(&Tree, "preorder.txt");

    TreeDump(&Tree, &LogCtx);
    TreeErr_t err = TreeVerify(&Tree);
    printf("err = %d\n", err);

    PrintPreOrder(Tree.root);
    printf("\n");

    DeleteNode(&Tree, "pizda");

    PrintPreOrder(Tree.root);
    printf("\n");

    TreeDump(&Tree, &LogCtx);

    TreeFree(Tree.root);

    return 0;
}