#include <stdio.h>
#include "Tree.h"

int main(void)
{
    Tree_t Tree = {};

    LogCtx_t LogCtx = {};
    TreeLogInit(&Tree, &LogCtx);

    PreOrderCtor(&Tree, "preorder.txt");

    PrintPreOrder(Tree.root);

    TreeDump(&Tree, &LogCtx);

    TreeFree(Tree.root);

    return 0;
}