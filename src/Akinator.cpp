#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdarg.h>
#include <unistd.h>
#include <ctype.h>
#include "Tree.h"
#include "Akinator.h"

TreeErr_t AkinatorPreOrderCtor(Tree_t *Tree, const char *file_name)
{
    return PreOrderCtor(Tree, file_name);
}

TreeErr_t AkinatorPostOrderCtor(Tree_t *Tree, const char *file_name)
{
    return PostOrderCtor(Tree, file_name);
}

TreeErr_t AkinatorInOrderCtor(Tree_t *Tree, const char *file_name)
{
    return InOrderCtor(Tree, file_name);
}

TreeErr_t AkinatorDtor(Tree_t *Tree)
{
    return TreeDtor(Tree);
}

void AkinatorStart(Tree_t *Tree, const char *file_name, ModeFlag_t mode_flag, LogCtx_t *LogCtx)
{
    char ch = 0;
    int fail = 0;
    TreeNode_t *Node = NULL;
    char NewNodeBuf[DATA_SIZE] = {};
    FILE *fp = fopen(file_name, "w");
    if (!fp)
        return;

    Greet();

    while (1)
    {
        SlowPrintf("Do you wanna continue? [Y/n]\n");

        scanf("%c", &ch);
        if (ch == 'n' || ch == 'N')
            break;

        Node = Guess(Tree, &fail, NewNodeBuf);

        if (fail)
            AddNew(Tree, Node, NewNodeBuf);

        switch(mode_flag)
        {
            case PREORDER:
                WritePreOrder(Tree->root, fp);
                break;

            case POSTORDER:
                WritePostOrder(Tree->root, fp);
                break;

            case INORDER:
                WriteInOrder(Tree->root, fp);
                break;

            default:
                ;
        }

        SlowPrintf("Do you wanna see TreeDump? [Y/n]\n");
        ClearBuf();
        scanf("%c", &ch);
        if (ch == 'y' || ch == 'Y')
        {
            TreeDump(Tree, LogCtx);
        }
        ClearBuf();
    }

    fclose(fp);
}

TreeNode_t *Guess(Tree_t *Tree, int *fail, char *NewNodeBuf)
{
    static char ch = 0;
    TreeNode_t *Node = Tree->root;
    if (!Node)
        return NULL;

    while (1)
    {
        SlowPrintf("Is it %s?\n", Node->data);
        ClearBuf();
        scanf("%c", &ch);

        if (ch == 'y' || ch == 'Y')
        {
            if (Node->left)
            {
                Node = Node->left;
                continue;
            }
            else 
            {
                SlowPrintf("Ura\n");
                *fail = 0;
                return Node;
            }
        }
        else if (ch == 'n' || ch == 'N')
        {
            if (Node->right)
            {
                Node = Node->right;
                continue;
            }
            else 
            {
                SlowPrintf("Then what is it?\n");
                ClearBuf();
                scanf("%s", NewNodeBuf);
                *fail = 1;
                return Node;
            }
        }
    }
}

TreeErr_t AddNew(Tree_t *Tree, TreeNode_t *Curr, char *NewNodeBuf)
{
    TreeNode_t *TempParent = Curr->parent;

    char AttributeBuf[DATA_SIZE] = {};

    SlowPrintf("What is the difference between %s and %s?\n", NewNodeBuf, Curr->data);
    SlowPrintf("%s...\n", NewNodeBuf);
    ClearBuf();
    scanf("%s", AttributeBuf);

    TreeNode_t *NewNode = CreateNode();
    if (!NewNode)
        return CALLOC_FAIL;

    NewNode->data = strdup(NewNodeBuf);
    if (!NewNode->data)
        return CALLOC_FAIL;

    TreeNode_t *AttributeNode = CreateNode();
    if (!AttributeNode)
        return CALLOC_FAIL;

    AttributeNode->data = strdup(AttributeBuf);
    if (!AttributeNode->data)
        return CALLOC_FAIL;

    if (Curr == TempParent->left)
        TempParent->left = AttributeNode;
    else if (Curr == TempParent->right)
        TempParent->right = AttributeNode;

    AttributeNode->parent = TempParent;
    AttributeNode->left = NewNode;
    AttributeNode->right = Curr;
    Curr->left = NULL;
    Curr->right = NULL;
    Curr->parent = AttributeNode;
    NewNode->parent = AttributeNode;

    return TREE_OK;
}

void Greet(void)
{
    SlowPrintf("###########################\n");
    SlowPrintf("---------AKINATOR----------\n");
    SlowPrintf("###########################\n");
}


void SlowPrintf(const char *fmt, ...)
{
    const int MAX_STR = 256;
    const int SLEEP_TIME = 10000;

    char buf[MAX_STR] = {};
    va_list args = {};

    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    va_end(args);
    
    char *ptr = buf;

    for (; *ptr; ptr++)
    {
        printf("%c", *ptr);
        fflush(stdout);

        usleep(SLEEP_TIME);
    }
}

int ClearBuf(void)
{
	int garbage = 0;
	int ch = 0;
	while ((ch = getchar()) != '\n')
		if (!isspace(ch))
			garbage = 1;
	return garbage;	
}