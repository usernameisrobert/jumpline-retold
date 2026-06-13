#include "renderer.h"
#include "player.h"
#include <inttypes.h>
#include <raylib.h>

void Renderer_Draw(Scene const* const scene) {
    BeginDrawing();
    ClearBackground(scene->bg_color);
    Player_Draw(&scene->player);
    EndDrawing();
}
