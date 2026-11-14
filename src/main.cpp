#include <stdio.h>
#include "Tree.h"
#include "Akinator.h"

int main(void)
{
    Tree_t Tree = {};

    LogCtx_t LogCtx = {};
    TreeLogInit(&LogCtx);

    AkinatorPreOrderCtor(&Tree, "clash_royale_preorder.txt");

    AkinatorStart(&Tree, "database/clash_royale_preorder.txt", PREORDER, &LogCtx);

    DefineNode(&Tree, "ice_spirit");

    Difference(&Tree, "sparky", "goblins");
    TreeDump(&Tree, &LogCtx);

    AkinatorDtor(&Tree);
    TreeLogDeinit(&LogCtx);

    return 0;
}