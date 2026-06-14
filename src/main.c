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
    const float gravity = 2000;

    scene->player.vel.y += gravity * dt; // good job on the gravity fomurar with is vel += gravity * dt^2 or
    scene->player.vel.x = scene->player.vel.x * 0.8;
    bool isgrounded = false;

    const float groundy = HEIGHT - scene->player.scale.y; // no hardcoding ground
    if (scene->player.pos.y > groundy) { // ground
        scene->player.pos.y = groundy;
        scene->player.vel.y = 0;
        isgrounded = true;
    }
    if (IsKeyPressed(KEY_SPACE) && isgrounded) {
        scene->player.vel.y = -800;
    }
    if (IsKeyDown(KEY_A)) {
        scene->player.vel.x -= 100;
    }
    if (IsKeyDown(KEY_D)) {
        scene->player.vel.x += 100;
    }

    scene->player.pos.y += scene->player.vel.y * dt;
    scene->player.pos.x += scene->player.vel.x * dt;
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
