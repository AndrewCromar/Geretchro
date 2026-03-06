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

    GameObject objectA;
    GameObject objectB;

    PlayerSettings playerSettings;

    void setup_player();

    void start()
    {
        // setup_player();
        // setup_ground();

        setup_test_objects();
    }

    void update(float dt)
    {
    }

    void setup_test_objects()
    {
        // same size square that overlapp a bit to test collision resolution

        // Object A
        objectA.transform->position.x = 50;
        objectA.transform->position.y = 50;
        Sprite* spriteA = objectA.addComponent<Sprite>();
        spriteA->draw = [spriteA]()
        {
            int x = spriteA->gameObject->transform->position.x;
            int y = spriteA->gameObject->transform->position.y;

            Graphics::rect(x, y, 20, 20, Colors::RED, true);
        };
        Renderer::register_sprite(spriteA);
        BoxCollider* colliderA = objectA.addComponent<BoxCollider>();
        colliderA->width = 20;
        colliderA->height = 20;
        Solver::register_collider(colliderA);
        
        // Object B
        objectB.transform->position.x = 60;
        objectB.transform->position.y = 60;
        Sprite* spriteB = objectB.addComponent<Sprite>();
        spriteB->draw = [spriteB]()
        {
            int x = spriteB->gameObject->transform->position.x;
            int y = spriteB->gameObject->transform->position.y;

            Graphics::rect(x, y, 20, 20, Colors::BLUE, true);
        };
        Renderer::register_sprite(spriteB);
        BoxCollider* colliderB = objectB.addComponent<BoxCollider>();
        colliderB->width = 20;
        colliderB->height = 20;
        Solver::register_collider(colliderB);
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