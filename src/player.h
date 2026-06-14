#pragma once
#include <raylib.h>

typedef struct player {
    Vector2 pos;
    Vector2 scale;
    Color color;
} Player;

void Player_Draw(const Player* const player);
