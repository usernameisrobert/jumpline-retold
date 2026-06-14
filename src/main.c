#include "raylib.h"
#include "renderer.h"
#include "game.h"

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

void UpdateFunction(float dt, Scene* scene) {
    // TODO: robort add player movment or what not you fucking retarted idiot i don't wanna do it
}

int main() {
    CreateWindow(WIDTH, HEIGHT, "Jumpline retold");

    mainsc = (Scene){
        .player = {
            .pos = { 0, 0},
            .scale = { 50, 50 },
            .color = RED,
        },
        .bg_color = GetColor(0x0F0F1FFF)
    };

    LoadScene(&mainsc);
    RegisterUpdate(&UpdateFunction);

    StartGameLoop();
    EndGameLoop();
    return 0;
}
