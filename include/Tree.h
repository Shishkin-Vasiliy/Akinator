#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef char* TreeElem_t;

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
    BAD_PTR,
    FILE_OPEN_FAIL,
    TREE_EMPTY,
    TREE_CORRUPTED
};

struct LogCtx_t {
    char **pict_index;
    size_t num_picts;
};

const int DATA_SIZE = 64;

TreeErr_t PreOrderCtor(Tree_t *Tree, const char *file_name);
TreeErr_t PostOrderCtor(Tree_t *Tree, const char *file_name);
TreeErr_t InOrderCtor(Tree_t *Tree, const char *file_name);

TreeErr_t TreeDtor(Tree_t *Tree);
TreeErr_t TreeFree(TreeNode_t *Curr);

TreeNode_t *CreateNode(void);

void PrintPreOrder(TreeNode_t *Node);
void PrintPostOrder(TreeNode_t *Node);
void PrintInOrder(TreeNode_t *Node);

void WritePreOrder(TreeNode_t *Node, FILE *fp);
void WritePostOrder(TreeNode_t *Node, FILE *fp);
void WriteInOrder(TreeNode_t *Node, FILE *fp);

int TreeLogInit(LogCtx_t *LogCtx);
int TreeLogDeinit(LogCtx_t *LogCtx);

int TreeDump(Tree_t *Tree, LogCtx_t *LogCtx);
void DrawTree(Tree_t *Tree, TreeNode_t *Curr, FILE *fp);
void DescribeTree(Tree_t *Tree, FILE *fp);

ssize_t GetFileSize(const char *file_name);
size_t ReadFromFile(char **buf, const char *file_name);

TreeNode_t *BuildFromPreOrder(Tree_t *Tree, TreeNode_t *Curr, char **buf);
TreeNode_t *BuildFromPostOrder(Tree_t *Tree, TreeNode_t *Curr, char **buf);
TreeNode_t *BuildFromInOrder(Tree_t *Tree, TreeNode_t *Curr, char **buf);

TreeNode_t *DeleteNode(Tree_t *Tree, const char *data);
TreeNode_t *FindNode(TreeNode_t *Curr, const char *data);
TreeNode_t *FindRightLeaf(TreeNode_t *Curr);

TreeErr_t TreeVerify(Tree_t *Tree);
TreeErr_t CheckNode(TreeNode_t *Node);

#endif