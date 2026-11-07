#include <stdio.h>
#include "Tree.h"

int main(void)
{
    Tree_t Tree = {};
    TreeErr_t err = TreeCtor(&Tree, 50);

    LogCtx_t LogCtx = {};
    TreeLogInit(&Tree, &LogCtx);

    TreeNode_t *Node20 = CreateNode(20);
    Tree.root->left = Node20;
    Node20->parent = Tree.root;

    TreeNode_t *Node10 = CreateNode(10);
    Node20->left = Node10;
    Node10->parent = Node20;

    TreeNode_t *Node30 = CreateNode(30);
    Node20->right = Node30;
    Node30->parent = Node20;

    TreeNode_t *Node60 = CreateNode(60);
    Tree.root->right = Node60;
    Node60->parent = Tree.root;

    TreeNode_t *Node52 = CreateNode(52);
    Node60->left = Node52;
    Node52->parent = Node60;

    TreeNode_t *Node69 = CreateNode(69);
    Node60->right = Node69;
    Node69->parent = Node60;

    PrintTree(Tree.root);

    TreeDump(&Tree, &LogCtx);

    TreeFree(Tree.root);

    return 0;
}