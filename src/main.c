#include "raylib.h"
#include "renderer.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

const int WIDTH = 800;
const int HEIGHT = 450;

Color BGblack;
Texture2D logo;
Vector2 logopos;

Scene mainsc;

void RenderDrawEmScripten() {
    Renderer_Draw(&mainsc);
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Jumpline Retold"); //hey look its title
    BGblack = GetColor(0x0F0F1FFF);

    mainsc = (Scene){
        .player = {
            .pos = { 0, 0},
            .scale = { 50, 50 },
            .color = RED,
        },
        .bg_color = GetColor(0x0F0F1FFF)
    };

    SetTargetFPS(60);
    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(RenderDrawEmScripten, 60, 1);
    #else
        SetTargetFPS(60);
        while (!WindowShouldClose()) {
            Renderer_Draw(&mainsc);
        }
    #endif

    CloseWindow();
    return 0;
}
