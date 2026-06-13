#include "raylib.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

const int WIDTH = 800;
const int HEIGHT = 450;

Color BGblack;
Texture2D logo;
Vector2 logopos;

void UpdateDrawFrame() {
    BeginDrawing();
        ClearBackground(BGblack);
        DrawTextureEx(logo, logopos, 0, 1, RAYWHITE);
    EndDrawing();
}

int main() {
    InitWindow(WIDTH, HEIGHT, "Jumpline Retold"); //hey look its title
    BGblack = GetColor(0x0F0F1FFF);
    logo = LoadTexture("assets/jumplineretoldsmall.png");
    SetTextureFilter(logo, TEXTURE_FILTER_BILINEAR);
    logopos = (Vector2){ (WIDTH / 2.0f) - logo.width / 2.0, HEIGHT / 2.0f - logo.height / 2.0};

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
