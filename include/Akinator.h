#ifndef AKINATOR_H
#define AKINATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Tree.h"

enum AkinatorErr_t {
    AKINATOR_OK
};

enum ModeFlag_t {
    PREORDER,
    POSTORDER,
    INORDER
};

void SlowPrintf(const char *fmt, ...);
int ClearBuf(void);
void Greet(void);
TreeErr_t AkinatorPreOrderCtor(Tree_t *Tree, const char *file_name);
TreeErr_t AkinatorPostOrderCtor(Tree_t *Tree, const char *file_name);
TreeErr_t AkinatorInOrderCtor(Tree_t *Tree, const char *file_name);
TreeErr_t AkinatorDtor(Tree_t *Tree);

void AkinatorStart(Tree_t *Tree, const char *file_name, ModeFlag_t mode_flag, LogCtx_t *LogCtx);
TreeNode_t *Guess(Tree_t *Tree, int *fail, char *NewNodeBuf);
TreeErr_t AddNew(Tree_t *Tree, TreeNode_t *Curr, char *NewNodeBuf);

#endif