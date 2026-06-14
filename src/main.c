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
    const float jump_speed = 800;
    const float move_speed = 100;

    scene->player.vel.y += gravity * dt; // good job on the gravity fomurar with is vel += gravity * dt^2 or
    scene->player.vel.x = scene->player.vel.x * 0.8;
    bool isgrounded = false;

    const float groundy = HEIGHT - scene->player.scale.y; // no hardcoding ground
    if (scene->player.pos.y >= groundy) { // ground
        scene->player.pos.y = groundy;
        scene->player.vel.y = 0;
        isgrounded = true;
    }
    if (( IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP) ) && isgrounded) {
        scene->player.vel.y = -jump_speed;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        scene->player.vel.x -= move_speed;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        scene->player.vel.x += move_speed;
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
        .bg_color = GetColor(0x0F0F1FFF),
        .objects = nullptr,
        .obj_cap = 0,
        .obj_count = 0,
    };

    Object white_square = {
        .pos = { 50, 50},
        .scale = { 150, 50 },
        .rotation = 23.31,
        .color = WHITE,
        .istextured = false
    };

    Object white_square2 = {
        .pos = { WIDTH - 150 - 50, 100 },
        .scale = { 150, 50 },
        .rotation = -23.31,
        .color = WHITE,
        .istextured = false
    };

    Scene_AddObjects(&mainsc, (Object[]) { white_square, white_square2 }, 2);
    LoadScene(&mainsc);
    RegisterUpdate(&UpdateFunction);

    StartGameLoop();
    EndGameLoop();
    Scene_Deinit(&mainsc);
    return 0;
}
