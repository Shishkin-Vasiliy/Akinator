#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctype.h>
#include <unistd.h>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#include "Tree.h"

enum AkinatorErr_t {
    AKINATOR_OK
};

enum ModeFlag_t {
    PREORDER,
    POSTORDER,
    INORDER
};

enum VisualFlag_t {
    GRAPHICS_FLAG,
    TERMINAL_FLAG
};

enum Answer_t {
    YES, 
    NO,
    DONTKNOW
};

void SlowPrintf(const char *fmt, ...);
int ClearBuf(void);
void Greet(VisualFlag_t flag);
void AskQuestion(const char *qustion, VisualFlag_t flag);
Answer_t GetAnswer(VisualFlag_t flag);
Answer_t HandleTerminalAnswer(void);

TreeErr_t AkinatorPreOrderCtor(Tree_t *Tree, const char *file_name, VisualFlag_t flag);
TreeErr_t AkinatorPostOrderCtor(Tree_t *Tree, const char *file_name, VisualFlag_t flag);
TreeErr_t AkinatorInOrderCtor(Tree_t *Tree, const char *file_name, VisualFlag_t flag);
TreeErr_t AkinatorDtor(Tree_t *Tree, VisualFlag_t flag);

void AkinatorStart(Tree_t *Tree, const char *file_name, ModeFlag_t mode_flag, LogCtx_t *LogCtx, VisualFlag_t flag);
TreeNode_t *Guess(Tree_t *Tree, int *fail, char *NewNodeBuf, VisualFlag_t flag);
TreeErr_t AddNew(Tree_t *Tree, TreeNode_t *Curr, char *NewNodeBuf);
size_t GetDefinition(TreeNode_t *root, const char *data, TreeNode_t **Definition);
TreeNode_t *DefineNode(Tree_t *Tree, const char *data);
void Difference(Tree_t *Tree, const char *data_1, const char *data_2);

#endif