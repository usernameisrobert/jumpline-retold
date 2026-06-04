#include "raylib.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Color BGblack;
Texture2D logo;
Vector2 logopos;

void UpdateDrawFrame(void) {
    BeginDrawing();
        ClearBackground(BGblack);
        DrawTextureEx(logo, logopos, 0, 0.1, RAYWHITE);
    EndDrawing();
}

int main(void) {
    InitWindow(800, 450, "Jumpline Retold"); //hey look its title
    BGblack = GetColor(0x0F0F1FFF);
    logo = LoadTexture("assets/jumplineretoldlogo.png");
    logopos = (Vector2){ 50.0f, 50.0f };

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateDrawFrame();
    }
#endif

    CloseWindow();
    return 0;
}
