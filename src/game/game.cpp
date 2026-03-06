#include <Arduino.h>
#include "core/gameObject.h"
#include "game.h"
#include "inputSystem/inputSystem.h"
#include "time/time.h"
#include "rendering/components/sprite.h"
#include "rendering/renderer.h"
#include "rendering/graphics.h"
#include "rendering/colors.h"

namespace Game
{
    struct PlayerSettings
    {
        float speed = 50;
        float jump_force = 20;
    };

    GameObject player;
    PlayerSettings playerSettings;

    void setup_player();

    void start()
    {
        setup_player();
    }

    void update(float dt)
    {
    }

    void setup_player()
    {
        player.transform->x = 80;
        player.transform->y = 60;

        Sprite* sprite = player.addComponent<Sprite>();

        sprite->draw = [&]()
        {
            int x = player.transform->x;
            int y = player.transform->y;

            Graphics::rect(x, y, 10, 10, Colors::WHITE, true);

            Graphics::rect(x + 2, y + 2, 2, 2, Colors::BLUE, true);
            Graphics::rect(x + 6, y + 2, 2, 2, Colors::BLUE, true);

            Graphics::rect(x + 2, y + 6, 6, 2, Colors::RED, true);
        };

        Renderer::register_sprite(sprite);
    }
}