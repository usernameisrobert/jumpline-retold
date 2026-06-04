#include "raylib.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Color BGblack;

void UpdateDrawFrame(void) {
    BeginDrawing();
        ClearBackground(BGblack);
        DrawTextureEx(logo, vec2(50, 50), 0, 1);
    EndDrawing();
}

int main(void) {
    BGblack = GetColor(0x0F0F1FFF);
    Texture2D logo = LoadTexture("assets/jumplineretoldlogo.png");
    InitWindow(800, 450, "Jumpline Retold"); //hey look its title

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
