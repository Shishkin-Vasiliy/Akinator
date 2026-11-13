#include "Tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

TreeErr_t PreOrderCtor(Tree_t *Tree, const char *file_name)
{
    char *buf = NULL;

    ReadFromFile(&buf, file_name);

    char *temp = buf;

    BuildFromPreOrder(Tree, Tree->root, &temp);

    free(buf);

    return TREE_OK;
}

TreeErr_t PostOrderCtor(Tree_t *Tree, const char *file_name)
{
    char *buf = NULL;

    ReadFromFile(&buf, file_name);

    char *temp = buf;

    BuildFromPostOrder(Tree, Tree->root, &temp);

    free(buf);

    return TREE_OK;
}

TreeErr_t InOrderCtor(Tree_t *Tree, const char *file_name)
{
    char *buf = NULL;

    ReadFromFile(&buf, file_name);

    char *temp = buf;

    BuildFromInOrder(Tree, Tree->root, &temp);

    free(buf);

    return TREE_OK;
}

TreeNode_t *CreateNode(void)
{
    TreeNode_t *Node = (TreeNode_t *)calloc(1, sizeof(TreeNode_t));
    if (Node)
    {
        Node->data = NULL;
        Node->left = NULL;
        Node->right = NULL;
        Node->parent = NULL;
    }
    return Node;
}

TreeNode_t *FindNode(TreeNode_t *Curr, const char *data)
{
    if (Curr == NULL)
        return NULL;

    if (strcmp(Curr->data, data) == 0)
        return Curr;

    if (strcmp(Curr->data, data) > 0)
        return FindNode(Curr->left, data);
    else if (strcmp(Curr->data, data) < 0)
        return FindNode(Curr->right, data);

    return NULL;
}

TreeNode_t *FindRightLeaf(TreeNode_t *Curr)
{
    if (!Curr)
        return NULL;

    if (Curr->right == NULL)
        return Curr;

    return FindRightLeaf(Curr->right);

    return NULL;
}

TreeNode_t *DeleteNode(Tree_t *Tree, const char *data)
{
    TreeNode_t *Curr = FindNode(Tree->root, data);

    if (!Curr)
        return NULL;

    TreeNode_t *TempLeft = Curr->left;
    TreeNode_t *TempRight = Curr->right;
    TreeNode_t *TempParent = Curr->parent;
    TreeNode_t *NewCurr = NULL;

    if (!(Curr->left) && !(Curr->right))
    {
        if (TempParent && TempParent->left == Curr)
            TempParent->left = NULL;
        else if (TempParent && TempParent->right == Curr)
            TempParent->right = NULL;
        else if (!TempParent && Tree->root == Curr)
            Tree->root = NULL;

        free(Curr->data);
        free(Curr);

        return NULL;
    }

    if (!TempLeft && TempRight)
        NewCurr = TempRight;
    else if (TempLeft && !TempRight)
        NewCurr = TempLeft;
    else 
        NewCurr = FindRightLeaf(TempLeft);

    if (Tree->root == Curr)
        Tree->root = NewCurr;

    else if (NewCurr->parent != Curr && !NewCurr->left)
        NewCurr->parent->right = NULL;
    else if (NewCurr->parent != Curr && NewCurr->left)
    {
        NewCurr->parent->right = NewCurr->left;
        NewCurr->left->parent = NewCurr->parent;
    }
   
    if (TempLeft && NewCurr != TempLeft)
    {
        NewCurr->left = TempLeft;
        TempLeft->parent = NewCurr;
    }

    if (TempRight && NewCurr->parent != Curr)
    {
        NewCurr->right = TempRight;
        TempRight->parent = NewCurr;
    }

    if (TempParent && TempParent->left == Curr)
        TempParent->left = NewCurr;
    else if (TempParent && TempParent->right == Curr)
        TempParent->right = NewCurr;
    else if (!TempParent)
    {
        if (TempRight)
        {
            NewCurr->right = TempRight;
            TempRight->parent = NewCurr;
        }
    }
 
    NewCurr->parent = TempParent;

    free(Curr->data);
    free(Curr);
    
    return NewCurr;
}

void PrintPreOrder(TreeNode_t *Node)
{
    if (!Node)
        return;

    printf("(");

    printf("%s", Node->data);

    if (Node->left)
        PrintPreOrder(Node->left);
    else if (Node->left == NULL && Node->right != NULL)
        printf("()");
    if (Node->right)
        PrintPreOrder(Node->right);
    else if (Node->right == NULL && Node->left != NULL)
        printf("()");

    printf(")");
}

void PrintPostOrder(TreeNode_t *Node)
{
    if (!Node)
        return;

    printf("(");

    if (Node->left)
        PrintPreOrder(Node->left);
    else if (Node->left == NULL && Node->right != NULL)
        printf("()");
    if (Node->right)
        PrintPreOrder(Node->right);
    else if (Node->right == NULL && Node->left != NULL)
        printf("()");

    printf("%s", Node->data);

    printf(")");
}

void PrintInOrder(TreeNode_t *Node)
{
    if (!Node)
        return;

    printf("(");

    if (Node->left)
        PrintPreOrder(Node->left);
    else if (Node->left == NULL && Node->right != NULL)
        printf("()");

    printf("%s", Node->data);

    if (Node->right)
        PrintPreOrder(Node->right);
    else if (Node->right == NULL && Node->left != NULL)
        printf("()");

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

    free(Curr->data);
    free(Curr);

    return TREE_OK;
}

int TreeLogInit(LogCtx_t *LogCtx)
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

int TreeLogDeinit(LogCtx_t *LogCtx)
{
    for (size_t i = 0; i < LogCtx->num_picts; i++)
        free(LogCtx->pict_index[i]);
    free(LogCtx->pict_index);

    return 0;
}

int TreeDump(Tree_t *Tree, LogCtx_t *LogCtx)
{
    const int PATH_SIZE    = 30;
    const int COMMAND_SIZE = 80;

    char dot_path[PATH_SIZE]   = {};
    char png_path[PATH_SIZE]   = {};
    char command[COMMAND_SIZE] = {};

    size_t num_picts = LogCtx->num_picts;

    snprintf(dot_path, PATH_SIZE, "TreeLog/pict_%lu.dot", num_picts);

    FILE *dot_fp = fopen(dot_path, "w");
    if (!dot_fp)
        return EOF;

    DescribeTree(Tree, dot_fp);
    fclose(dot_fp);

    snprintf(command, COMMAND_SIZE, "dot %s -Tpng -o TreeLog/pict_%lu.png", dot_path, num_picts);
    system(command);

    snprintf(png_path, PATH_SIZE, "pict_%lu.png", num_picts);

    char *temp = strdup(png_path);
    if (!temp)
        return EOF;

    LogCtx->pict_index[num_picts] = temp;
    LogCtx->num_picts++;

    return 0;
}

void DescribeTree(Tree_t *Tree, FILE *fp)
{
    if (!fp)
        return;

    fprintf(fp, "digraph {\n");
    fprintf(fp, "bgcolor=\"#FFE4E1\";\n");
    fprintf(fp, "rankdir=TB;\n");      
    fprintf(fp, "nodesep=0.8;\n");
    fprintf(fp, "ranksep=0.9;\n");

    DrawTree(Tree, Tree->root, fp);

    fprintf(fp, "}\n");
}

void DrawTree(Tree_t *Tree, TreeNode_t *Curr, FILE *fp)
{  
    fprintf(fp, "node_%s [shape=Mrecord; style=filled; fillcolor=\"#DB7093\"; fontcolor=\"#FFFFFF\";\n", Curr->data);
    fprintf(fp, "       label=\"%s\"];\n", Curr->data);

    if (Curr == Tree->root)
        fprintf(fp, "{ rank=source; node_%s };\n", Tree->root->data);

    if (Curr->left)
        DrawTree(Tree, Curr->left, fp);
    if (Curr->right)
        DrawTree(Tree, Curr->right, fp);

    if (!(Curr->left) && !(Curr->right))
        fprintf(fp, "{ rank=sink; node_%s };\n", Curr->data);

    if (Curr != Tree->root)
    {
        if (Curr == Curr->parent->left)
        {
            fprintf(fp, "edge [color=\"#FFFFFF\"];\n");
            fprintf(fp, "node_%s -> node_%s [label = \"DA\"; color=\"#228B22\"]\n;", Curr->parent->data, Curr->data);
        }
        else if (Curr == Curr->parent->right)
        {
            fprintf(fp, "edge [color=\"#FFFFFF\"];\n");
            fprintf(fp, "node_%s -> node_%s [label = \"NET\"; color=\"#DC143C\"]\n;", Curr->parent->data, Curr->data);
        }
    }
    
    return;
}

ssize_t GetFileSize(const char *file_name)
{
    struct stat stat_buf = {};
    stat(file_name, &stat_buf);

    return stat_buf.st_size;
}

size_t ReadFromFile(char **buf, const char *file_name)
{   
    FILE *fp = fopen(file_name, "r");
    if (!fp)
        return 0;

    ssize_t file_size = GetFileSize(file_name);

    *buf = (char *)calloc((size_t)file_size, sizeof(char));
    if (!buf)
        return 0;

    size_t count = fread(*buf, sizeof(char), (size_t)file_size, fp);

    fclose(fp);

    return count;
}

TreeNode_t *BuildFromPreOrder(Tree_t *Tree, TreeNode_t *Curr, char **buf)
{
    char data[DATA_SIZE] = {};
    size_t len = 0;
    int num_elems = 0;

    if (**buf == '(')
    {
        Curr = CreateNode();
        if (!Tree->root)
            Tree->root = Curr;
        (*buf)++; 
    }

    num_elems = sscanf(*buf, "%[^()]", data);
    if (num_elems == 1)
    {
        len = strlen(data);
        (*buf) += len;
        TreeElem_t temp = strdup(data);
        if (temp)
            Curr->data = temp;
        else
            return NULL;
    }
    else
    {
        (*buf)++;
        return NULL;
    }

    if (**buf == '(')
    {
        Curr->left = BuildFromPreOrder(Tree, Curr->left, buf);
        if (Curr->left)
            (Curr->left)->parent = Curr;
    }

    if (**buf == ')')
    {
        (*buf)++;
        return Curr;
    }

    if (**buf == '(')
    {
        Curr->right = BuildFromPreOrder(Tree, Curr->right, buf);
        if (Curr->right)
            (Curr->right)->parent = Curr;
    }

    if (**buf == ')')
    {
        (*buf)++;
        return Curr;
    }

    return Curr;
}


TreeNode_t *BuildFromPostOrder(Tree_t *Tree, TreeNode_t *Curr, char **buf)
{
    char data[DATA_SIZE] = {};
    size_t len = 0;
    int num_elems = 0;

    if (**buf == '(')
    {
        Curr = CreateNode();
        if (!Tree->root)
            Tree->root = Curr;
        (*buf)++;
    }

    if (**buf == '(')
    {
        Curr->left = BuildFromPostOrder(Tree, Curr->left, buf);
        if (Curr->left)
            (Curr->left)->parent = Curr;
    }

    if (**buf == '(')
    {
        Curr->right = BuildFromPostOrder(Tree, Curr->right, buf);
        if (Curr->right)
            (Curr->right)->parent = Curr;
    }

    num_elems = sscanf(*buf, "%[^()]", data);
    if (num_elems == 1)
    {
        len = strlen(data);
        TreeElem_t temp = strdup(data);
        if (temp)
            Curr->data = temp;
        else 
            return NULL;
        (*buf) += len;       
    }
    else
    {
        (*buf)++;
        return NULL;
    }

    if (**buf == ')')
    {
        (*buf)++;
        return Curr;
    }

    return Curr;
}


TreeNode_t *BuildFromInOrder(Tree_t *Tree, TreeNode_t *Curr, char **buf)
{
    char data[DATA_SIZE] = {};
    size_t len = 0;
    int num_elems = 0;

    if (**buf == '(')
    {
        Curr = CreateNode();
        if (!Tree->root)
            Tree->root = Curr;
        (*buf)++;
    }

    if (**buf == '(')
    {
        Curr->left = BuildFromInOrder(Tree, Curr->left, buf);
        if (Curr->left)
            (Curr->left)->parent = Curr;
    }

    num_elems = sscanf(*buf, "%[^()]", data);
    if (num_elems == 1)
    {
        len = strlen(data);
        TreeElem_t temp = strdup(data);
        if (temp)
            Curr->data = temp;
        else
            return NULL;
        (*buf) += len;          
    }
    else
    {
        (*buf)++;
        return NULL;
    }

    if (**buf == ')')
    {
        (*buf)++;
        return Curr;
    }


    if (**buf == '(')
    {
        Curr->right = BuildFromInOrder(Tree, Curr->right, buf);
        if (Curr->right)
            (Curr->right)->parent = Curr;
    }
 
    if (**buf == ')')
    {
        (*buf)++;
        return Curr;
    }

    return Curr;
}

TreeErr_t TreeVerify(Tree_t *Tree)
{
    if (!Tree->root)
        return TREE_EMPTY;
    return CheckNode(Tree->root);
}

TreeErr_t CheckNode(TreeNode_t *Node)
{
    if (Node->left && strcmp(Node->data, Node->left->data) < 0)
        return TREE_CORRUPTED;
    if (Node->right && strcmp(Node->data, Node->right->data) > 0)
        return TREE_CORRUPTED;

    if (Node->left)
        CheckNode(Node->left);
    if (Node->right)
        CheckNode(Node->right);

    return TREE_OK;
}

void WritePreOrder(TreeNode_t *Node, FILE *fp)
{
    if (!Node)
        return;

    fprintf(fp, "(");

    fprintf(fp, "%s", Node->data);

    if (Node->left)
        WritePreOrder(Node->left, fp);
    else if (Node->left == NULL && Node->right != NULL)
        fprintf(fp, "()");
    if (Node->right)
        WritePreOrder(Node->right, fp);
    else if (Node->right == NULL && Node->left != NULL)
        fprintf(fp, "()");

    fprintf(fp, ")");
}

void WritePostOrder(TreeNode_t *Node, FILE *fp)
{
    if (!Node)
        return;

    fprintf(fp, "(");

    if (Node->left)
        WritePostOrder(Node->left, fp);
    else if (Node->left == NULL && Node->right != NULL)
        fprintf(fp, "()");

    if (Node->right)
        WritePostOrder(Node->right, fp);
    else if (Node->right == NULL && Node->left != NULL)
        fprintf(fp, "()");

    fprintf(fp, "%s", Node->data);

    fprintf(fp, ")");
}

void WriteInOrder(TreeNode_t *Node, FILE *fp)
{
    if (!Node)
        return;

    fprintf(fp, "(");

    if (Node->left)
        WriteInOrder(Node->left, fp);
    else if (Node->left == NULL && Node->right != NULL)
        fprintf(fp, "()");

    fprintf(fp, "%s", Node->data);

    if (Node->right)
        WriteInOrder(Node->right, fp);
    else if (Node->right == NULL && Node->left != NULL)
        fprintf(fp, "()");

    fprintf(fp, ")");
}