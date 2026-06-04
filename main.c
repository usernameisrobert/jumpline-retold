#include "raylib.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

Color BGblack;

void UpdateDrawFrame(void) {
    BeginDrawing();
        ClearBackground(blackcuzidkcolors);
        DrawText("so stinky", 190, 200, 20, RAYWHITE);
    EndDrawing();
}

int main(void) {
    BGblack = GetColor(0x0F0F1FFF);
    InitWindow(800, 450, "so stinky"); //so stinkyy

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
