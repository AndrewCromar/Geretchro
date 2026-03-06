#include "game.h"
#include "../graphics/graphicsengine.h"
#include "../inputs/inputs.h"

float player_x = 80;
float player_y = 60;
float speed = 50.0f;

void draw_player(float x, float y) {
    rect((int)x, (int)y, 10, 10, G_WHITE, true);
}

void update(float deltaTime) {
    if (button_up_input)    player_y -= speed * deltaTime;
    if (button_down_input)  player_y += speed * deltaTime;
    if (button_left_input)  player_x -= speed * deltaTime;
    if (button_right_input) player_x += speed * deltaTime;

    draw_player(player_x, player_y);
}