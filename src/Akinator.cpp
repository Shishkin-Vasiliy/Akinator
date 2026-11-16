#include "Tree.h"
#include "Akinator.h"
#include "Graphics.h"

TreeErr_t AkinatorPreOrderCtor(Tree_t *Tree, const char *file_name, VisualFlag_t flag)
{
    if (flag == GRAPHICS_FLAG)
        InitGraphics();
    return PreOrderCtor(Tree, file_name);
}

TreeErr_t AkinatorPostOrderCtor(Tree_t *Tree, const char *file_name, VisualFlag_t flag)
{
    if (flag == GRAPHICS_FLAG)
        InitGraphics();
    return PostOrderCtor(Tree, file_name);
}

TreeErr_t AkinatorInOrderCtor(Tree_t *Tree, const char *file_name, VisualFlag_t flag)
{
    if (flag == GRAPHICS_FLAG)
        InitGraphics();
    return InOrderCtor(Tree, file_name);
}

TreeErr_t AkinatorDtor(Tree_t *Tree, VisualFlag_t flag)
{
    if (flag == GRAPHICS_FLAG)
        CloseWindow();
    return TreeDtor(Tree);
}

void AkinatorStart(Tree_t *Tree, const char *file_name, ModeFlag_t mode_flag, LogCtx_t *LogCtx, VisualFlag_t flag)
{
    Answer_t answer = DONTKNOW;
    int fail = 0;
    TreeNode_t *Node = NULL;
    char NewNodeBuf[DATA_SIZE] = {};
    FILE *fp = fopen(file_name, "w");
    if (!fp)
        return;

    Greet(flag);

    while (true)
    {
        answer = DONTKNOW;

        if (flag == TERMINAL_FLAG) 
            ClearBuf();
        AskQuestion("Do you wanna continue? [Y/n]\n", flag);

        while (answer != YES && answer != NO)
            answer = GetAnswer("Do you wanna continue? [Y/n]\n", flag);
        if (answer != YES)
            break;

        Node = Guess(Tree, &fail, NewNodeBuf, flag);

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
        answer = DONTKNOW;

        AskQuestion("Do you wanna see TreeDump? [Y/n]\n", flag);

        if (flag == TERMINAL_FLAG) 
            ClearBuf();
        while (answer != YES && answer != NO)
            answer = GetAnswer("Do you wanna see TreeDump? [Y/n]\n", flag);

        if (answer == YES)
            TreeDump(Tree, LogCtx);

        else 
            SlowPrintf("Press any key\n");

        ClearBuf();
    }

    fclose(fp);
}

TreeNode_t *Guess(Tree_t *Tree, int *fail, char *NewNodeBuf, VisualFlag_t flag)
{
    Answer_t answer = DONTKNOW;
    static char ch = 0;
    const int BUF_SIZE = 64;
    char buf[BUF_SIZE] = {};
    TreeNode_t *Node = Tree->root;
    if (!Node)
        return NULL;

    while (1)
    {
        answer = DONTKNOW;

        snprintf(buf, BUF_SIZE, "Is it %s?\n", Node->data);
        AskQuestion(buf, flag);
        if (flag == TERMINAL_FLAG) 
            ClearBuf();
        while (answer != YES && answer != NO)
            answer = GetAnswer(buf, flag);
        if (answer == YES)
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
        else if (answer == NO)
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
 
TreeNode_t *DefineNode(Tree_t *Tree, const char *data)
{
    TreeNode_t *Definition[MAX_HEIGHT] = {};

    size_t count = GetDefinition(Tree->root, data, Definition);
    SlowPrintf("%s ", data);
    for (; count > 0; --count)
    {
        SlowPrintf("%s, ", (Definition[count])->data);
    }
    printf("\n");

    return Tree->root;
}

size_t GetDefinition(TreeNode_t *root, const char *data, TreeNode_t **Definition)
{
    size_t i = 0;
    TreeNode_t *Node = FindPreOrder(root, data);
    if (!Node)
        return 0;

    do
    {
        Definition[i] = Node;
        Node = Node->parent;
        i++;
    } while (Node);

    return i - 1;
}

void Difference(Tree_t *Tree, const char *data_1, const char *data_2)
{
    TreeNode_t *Definition_1[MAX_HEIGHT] = {};
    size_t count_1 = GetDefinition(Tree->root, data_1, Definition_1);

    TreeNode_t *Definition_2[MAX_HEIGHT] = {};
    size_t count_2 = GetDefinition(Tree->root, data_2, Definition_2);

    SlowPrintf("%s and %s in common ", data_1, data_2);
    size_t i = 0;
    for (; i < count_1 && i < count_2; i++)
    {
        if (Definition_1[i] == Definition_2[i])
        {
            SlowPrintf("%s ", (Definition_1[i]->data));
        }
        else
        {
            i++;
            break;
        }
    }
    printf("\n");

    if (i < count_1 || i < count_2)
    {
        SlowPrintf("%s ", data_1);
        for (size_t j = i; j < count_1; j++)
        {
            SlowPrintf("%s ", (Definition_1[j])->data);
        }
        printf("\n");
        SlowPrintf("%s ", data_2);
        for (size_t j = i; j < count_2; j++)
        {
            SlowPrintf("%s ", (Definition_2[j])->data);
        }
        printf("\n");
    }
}
 
void Greet(VisualFlag_t flag)
{
    //if (flag == GRAPHICS_FLAG)  
    //    RenderGreet();
    //else
    //{
        SlowPrintf("###########################\n");
        SlowPrintf("---------AKINATOR----------\n");
        SlowPrintf("###########################\n\n");   
    //}
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

void AskQuestion(const char *question, VisualFlag_t flag)
{
    if (flag == GRAPHICS_FLAG)
        RenderQuestion(question);
    else
        SlowPrintf("%s\n", question);
}

Answer_t GetAnswer(const char *question, VisualFlag_t flag)
{
    if (flag == GRAPHICS_FLAG)
        return HandleGraphicsAnswer(question);
    else 
    {
        return HandleTerminalAnswer();
    }
}

Answer_t HandleTerminalAnswer(void)
{
    char ch = 0;
    scanf("%c", &ch);

    if (ch == 'n' || ch == 'N')
        return NO;
    else return YES;
}


