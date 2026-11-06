#include <stdio.h>
#include "Tree.h"

int main(void)
{
    Tree_t Tree = {};
    TreeErr_t err = TreeCtor(&Tree, 50);
    if (err)
        printf("Creating err\n");

    TreeNode_t *Node20 = CreateNode(20);
    Tree.root->left = Node20;

    TreeNode_t *Node10 = CreateNode(10);
    Node20->left = Node10;

    TreeNode_t *Node30 = CreateNode(30);
    Node20->right = Node30;

    TreeNode_t *Node60 = CreateNode(60);
    Tree.root->right = Node60;

    TreeNode_t *Node52 = CreateNode(52);
    Node60->left = Node52;

    TreeNode_t *Node69 = CreateNode(69);
    Node60->right = Node69;

    PrintTree(Tree.root);

    TreeFree(Tree.root);

    return 0;
}