#include <stdio.h>
#include "Tree.h"
#include "Akinator.h"
#include "Graphics.h"

int main(void)
{
    Tree_t Tree = {};

    LogCtx_t LogCtx = {};
    TreeLogInit(&LogCtx);

    AkinatorPreOrderCtor(&Tree, "clash_royale_preorder.txt", TERMINAL_FLAG);

    AkinatorStart(&Tree, "database/clash_royale_preorder.txt", PREORDER, &LogCtx, TERMINAL_FLAG);

    //DefineNode(&Tree, "ice_spirit");

    //Difference(&Tree, "sparky", "goblins");

    AkinatorDtor(&Tree, TERMINAL_FLAG);
    TreeLogDeinit(&LogCtx);

    return 0;
}