#ifndef TREE_H
#define TREE_H

typedef int TreeElem_t;

#define POIZON_VAL 0x0D01B0EB

struct TreeNode_t {
    TreeElem_t data;
    TreeNode_t *left;
    TreeNode_t *right;
    TreeNode_t *parent;
};

struct Tree_t {
    TreeNode_t *root;
};

enum TreeErr_t {
    TREE_OK,
    CALLOC_FAIL,
    BAD_PTR
};

TreeErr_t TreeCtor(Tree_t *Tree, TreeElem_t root_data);
TreeErr_t TreeDtor(Tree_t *Tree);
TreeErr_t TreeFree(TreeNode_t *Curr);
TreeNode_t *CreateNode(TreeElem_t data);
void PrintTree(TreeNode_t *Node);
void TreeDump(Tree_t *Tree);

#endif