#include "Akinator.h"
#include "Graphics.h"

Camera2D camera = { 0 };

void InitGraphics()
{
    SetTraceLogLevel(LOG_NONE);     
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "");

    camera.target = (Vector2){ 0.0f, 0.0f };      
    camera.offset = (Vector2){ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }; 
    camera.rotation = 0.0f;                       
    camera.zoom = 1.0f;

    SetTargetFPS(60);
}

void RenderQuestion(const char *question)
{
    BeginDrawing();
    BeginMode2D(camera);

    ClearBackground(RAYWHITE);

    DrawRectangle(X_ZERO - QuestRectWidth / 2, Y_ZERO - 300, QuestRectWidth, QuestRectHeight, PINK);
    DrawRectangle(X_ZERO - SCREEN_WIDTH / 2 + 30, Y_ZERO, AnsRectWidth, AnsRectHeight, GREEN);
    DrawRectangle(X_ZERO + SCREEN_WIDTH / 2 - AnsRectWidth - 30, Y_ZERO, AnsRectWidth, AnsRectHeight, RED);

    DrawText(question, X_ZERO - QuestRectWidth / 2 + 30, Y_ZERO - 300 + QuestRectHeight / 2, QuestFontSize, RAYWHITE);
    DrawText("YES", X_ZERO - SCREEN_WIDTH / 2 + 40, Y_ZERO, AnsFontSize, RAYWHITE);
    DrawText("NO", X_ZERO + SCREEN_WIDTH / 2 - AnsRectWidth - 20, Y_ZERO, AnsFontSize, RAYWHITE);

    EndMode2D();
    EndDrawing();
}

Answer_t HandleGraphicsAnswer(const char *question)
{
    while (!WindowShouldClose())
    {
        RenderQuestion(question);
        Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera);

        Rectangle YesRect = { X_ZERO - SCREEN_WIDTH / 2 + 30, Y_ZERO, AnsRectWidth, AnsRectHeight };
        Rectangle NoRect  = { X_ZERO + SCREEN_WIDTH / 2 - AnsRectWidth - 30, Y_ZERO, AnsRectWidth, AnsRectHeight };

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (CheckCollisionPointRec(mouse, YesRect))
                return YES;

            if (CheckCollisionPointRec(mouse, NoRect))
                return NO;
        }
    }

    return NO;
}

//void RenderGreet(void)
//{
//    BeginDrawing();
//
//    ClearBackground(RAYWHITE);
//
//    DrawRectangle(X_ZERO - GreetRectWidth / 2, Y_ZERO - GreetRectHeight / 2, GreetRectWidth, GreetRectHeight, PINK);
//    DrawText("AKINATOR", X_ZERO - GreetRectWidth / 2 + 40, Y_ZERO, GreetFontSize, RAYWHITE);
//
//    EndDrawing();
//}