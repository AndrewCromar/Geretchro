#include <Arduino.h>
#include "core/gameObject.h"
#include "game.h"
#include "inputSystem/inputSystem.h"
#include "physics/solver.h"
#include "physics/components/boxCollider.h"
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

        int width = 10;
        int height = 10;
    };

    GameObject player;
    GameObject ground;

    PlayerSettings playerSettings;

    void setup_player();

    void start()
    {
        setup_player();
        setup_ground();
    }

    void update(float dt)
    {
    }

    void setup_player()
    {
        // Position
        player.transform->position.x = 80;
        player.transform->position.y = 60;

        // Sprite
        Sprite* sprite = player.addComponent<Sprite>();

        sprite->draw = [sprite]()
        {
            int x = sprite->gameObject->transform->position.x;
            int y = sprite->gameObject->transform->position.y;

            Graphics::rect(x, y, 10, 10, Colors::WHITE, true);

            Graphics::rect(x + 2, y + 2, 2, 2, Colors::BLUE, true);
            Graphics::rect(x + 6, y + 2, 2, 2, Colors::BLUE, true);

            Graphics::rect(x + 2, y + 6, 6, 2, Colors::RED, true);
        };

        Renderer::register_sprite(sprite);

        // Collider
        BoxCollider* collider = player.addComponent<BoxCollider>();
        collider->width = playerSettings.width;
        collider->height = playerSettings.height;

        Solver::register_collider(collider);
    }

    void setup_ground()
    {
        // Position
        ground.transform->position.x = 0;
        ground.transform->position.y = Graphics::displaySettings.height - 1;

        // Sprite
        Sprite* sprite = ground.addComponent<Sprite>();
        sprite->draw = [sprite]()
        {
            Transform::Position position = sprite->gameObject->transform->position;

            Graphics::rect(0, position.x, position.y, 1, Colors::GREEN, true);
        };

        Renderer::register_sprite(sprite);

        // Collider
        BoxCollider* collider = ground.addComponent<BoxCollider>();
        collider->width = Graphics::displaySettings.width;
        collider->height = 1;
        
        Solver::register_collider(collider);
    }
}