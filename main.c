#include "raylib.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

void UpdateDrawFrame(void) {
    BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("so stinky", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
}

int main(void) {
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
