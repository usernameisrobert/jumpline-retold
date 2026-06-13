#pragma once
#include "player.h"
#include <raylib.h>

typedef struct scene {
    Color bg_color;
    Player player;
} Scene ;

void Renderer_Draw(Scene const* const scene);
