#include <stdio.h>
#include "Tree.h"
#include "Akinator.h"

int main(void)
{
    Tree_t Tree = {};

    LogCtx_t LogCtx = {};
    TreeLogInit(&LogCtx);

    AkinatorPreOrderCtor(&Tree, "preorder.txt");

    AkinatorStart(&Tree, "preorder.txt", PREORDER, &LogCtx);

    DeleteNode(&Tree, "hahaha");

    DeleteNode(&Tree, "netnetnet");

    DeleteNode(&Tree, "dadada");

    TreeDump(&Tree, &LogCtx);

    TreeDtor(&Tree);
    TreeLogDeinit(&LogCtx);

    return 0;
}