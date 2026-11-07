#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int TreeLogInit(Tree_t *Tree, LogCtx_t *LogCtx)
{
    const int MAX_PICTS = 16;
    int DirNotFound = system("[ -d TreeLog ]");

    if (DirNotFound)
    {
        int err = system("mkdir TreeLog");
        if (err)
        {
            return EOF;
        }
    }
    else 
    {
        system("rm -f TreeLog/*");
    }

    LogCtx->pict_index = (char **)calloc(MAX_PICTS, sizeof(char *));
    if (!LogCtx->pict_index)
        return EOF;

    return 0;
}

int TreeDump(Tree_t *Tree, LogCtx_t *LogCtx)
{
    const int PATH_SIZE    = 30;
    const int COMMAND_SIZE = 80;

    char dot_path[PATH_SIZE]   = {};
    char png_path[PATH_SIZE]   = {};
    char command[COMMAND_SIZE] = {};

    int num_picts = LogCtx->num_picts;

    snprintf(dot_path, PATH_SIZE, "TreeLog/pict_%d.dot", num_picts);

    FILE *dot_fp = fopen(dot_path, "w");
    if (!dot_fp)
        return EOF;

    DescribeTree(Tree, dot_fp);
    fclose(dot_fp);

    snprintf(command, COMMAND_SIZE, "dot %s -Tpng -o TreeLog/pict_%d.png", dot_path, num_picts);
    system(command);

    snprintf(png_path, PATH_SIZE, "pict_%d.png", num_picts);

    char *temp = strdup(png_path);
    if (!temp)
        return EOF;

    LogCtx->pict_index[num_picts] = temp;
    num_picts++;

    return 0;
}

void DescribeTree(Tree_t *Tree, FILE *fp)
{
    if (!fp)
        return;

    fprintf(fp, "digraph {\n");
    fprintf(fp, "bgcolor=\"#283f3f\";\n");
    fprintf(fp, "rankdir=TB;\n");      
    fprintf(fp, "nodesep=0.8;\n");
    fprintf(fp, "ranksep=0.9;\n");

    DrawTree(Tree, Tree->root, fp);

    fprintf(fp, "}\n");
}

void DrawTree(Tree_t *Tree, TreeNode_t *Curr, FILE *fp)
{  
    fprintf(fp, "node%d [shape=circle; style=filled; fillcolor=\"#6A184DA0\"; fontcolor=\"#FFFFFF\";\n", Curr->data);
    fprintf(fp, "       label=\"%d\"];\n", Curr->data);

    if (Curr == Tree->root)
        fprintf(fp, "{ rank=source; node%d };\n", Tree->root->data);

    if (Curr->left)
        DrawTree(Tree, Curr->left, fp);
    if (Curr->right)
        DrawTree(Tree, Curr->right, fp);

    if (!(Curr->left) && !(Curr->right))
        fprintf(fp, "{ rank=sink; node%d };\n", Curr->data);

    if (Curr != Tree->root)
    {
        fprintf(fp, "edge [color=\"#FFFFFF\"];\n");
        fprintf(fp, "node%d -> node%d\n;", Curr->parent->data, Curr->data);
    }
    
    return;
}