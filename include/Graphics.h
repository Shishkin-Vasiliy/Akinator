#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

extern Camera2D camera;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int X_ZERO = 0;
const int Y_ZERO = 0;
const int LINE_THICKNESS = 3;

const int GreetRectWidth = 600;
const int GreetRectHeight = 300;
const int GreetFontSize = 100;
const int QuestRectWidth = 400;
const int QuestRectHeight = 100;
const int QuestFontSize = 20;
const int AnsRectWidth = 200;
const int AnsRectHeight = 200;
const int AnsFontSize = 40; 

//void RenderGreet(void);
void RenderQuestion(const char *question);
void InitGraphics(void);
void RenderQuestion(const char *qustion);
Answer_t HandleGraphicsAnswer(void);

#endif