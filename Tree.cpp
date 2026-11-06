#include "Tree.h"
#include <stdio.h>
#include <cstdlib>

TreeErr_t TreeCtor(Tree_t *Tree, TreeElem_t root_data)
{
    TreeNode_t *temp = CreateNode(root_data);
    if (!temp)
        return CALLOC_FAIL;
    Tree->root = temp;

    return TREE_OK;
}

TreeNode_t *CreateNode(TreeElem_t data)
{
    TreeNode_t *Node = (TreeNode_t *)calloc(1, sizeof(TreeNode_t));
    if (Node)
        Node->data = data;
    return Node;
}

void PrintTree(TreeNode_t *Node)
{
    if (!Node)
        return;

    printf("(");

    printf("%d", Node->data);

    if (Node->left)
        PrintTree(Node->left);
    if (Node->right)
        PrintTree(Node->right);

    printf(")");
}

TreeErr_t TreeDtor(Tree_t *Tree)
{
    return TreeFree(Tree->root);
}

TreeErr_t TreeFree(TreeNode_t *Curr)
{
    if (!Curr)
        return BAD_PTR;

    if (Curr->left)
        TreeFree(Curr->left);
    if (Curr->right)
        TreeFree(Curr->right);

    free(Curr);

    return TREE_OK;
}



