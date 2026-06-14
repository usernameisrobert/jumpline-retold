#include "player.h"
#include <raylib.h>

void Player_Draw(const Player* const player) {
    DrawRectangle(player->pos.x, player->pos.y, player->scale.x, player->scale.y, player->color);
}
