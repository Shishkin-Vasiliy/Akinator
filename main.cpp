#include <stdio.h>
#include "Tree.h"

int main(void)
{
    Tree_t Tree = {};

    LogCtx_t LogCtx = {};
    TreeLogInit(&Tree, &LogCtx);

    InOrderCtor(&Tree, "inorder.txt");

    PrintInOrder(Tree.root);

    TreeDump(&Tree, &LogCtx);

    TreeFree(Tree.root);

    return 0;
}