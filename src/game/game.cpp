#include "game.h"
#include "../graphics/graphicsengine.h"
#include "../inputs/inputs.h"

float player_size_x = 10;
float player_size_y = 10;

float player_x = 80;
float player_y = 60;
float speed = 50.0f;

float jump_force = 20;

float ground_friction = 0.9f;
float air_friction = 0.99f;

float player_velocity_x = 0;
float player_velocity_y = 0;

float gravity = 9.81f;
float gravity_multiplier = 2.5f;

int screen_size_x = 160;
int screen_size_y = 120;

bool is_grounded = false;

void draw_player() {
    rect((int)player_x, (int)player_y, player_size_x, player_size_y, G_WHITE, true);

    rect((int)player_x + 2, (int)player_y + 2, 2, 2, G_BLUE, true);
    rect((int)player_x + 6, (int)player_y + 2, 2, 2, G_BLUE, true);

    rect((int)player_x + 2, (int)player_y + 6, 6, 2, G_RED, true);
}

void draw_ground() {
    rect(0, screen_size_y - 1, screen_size_x, 1, G_GREEN, true);
}

void apply_gravity(float deltaTime)
{
    player_velocity_y += gravity * gravity_multiplier * deltaTime;
}

void  clamp_player_position_to_screen()
{
    if (player_x < 0) 
    {
        player_velocity_x = 0;
        player_x = 0;
    }
    if (player_x > screen_size_x - 10)
    {
        player_velocity_x = 0;
        player_x = screen_size_x - 10;
    }
    if (player_y < 0)
    {
        player_velocity_y = 0;
        player_y = 0;
    }
    if (player_y > screen_size_y - 10)
    {
        player_velocity_y = 0;
        player_y = screen_size_y - 10;
    }
}

bool check_player_grounded()
{
    return player_y >= screen_size_y - player_size_y - 1;
}

void apply_friction()
{
    if (is_grounded)
    {
        player_velocity_x *= ground_friction;
    }
    else
    {
        player_velocity_x *= air_friction;
    }
}

void update(float deltaTime) {
    if (button_up_input && is_grounded) player_velocity_y = -jump_force;
    // if (button_down_input)              player_velocity_y += speed * deltaTime;
    if (button_left_input)              player_velocity_x -= speed * deltaTime;
    if (button_right_input)             player_velocity_x += speed * deltaTime;

    apply_gravity(deltaTime);
    clamp_player_position_to_screen();
    is_grounded = check_player_grounded();
    apply_friction();

    player_x += player_velocity_x * deltaTime;
    player_y += player_velocity_y * deltaTime;

    draw_player();
    draw_ground();
}