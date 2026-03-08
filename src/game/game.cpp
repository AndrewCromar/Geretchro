#include <Arduino.h>
#include "core/gameObject.h"
#include "game.h"
#include "inputSystem/inputSystem.h"
#include "physics/solver.h"
#include "physics/components/boxCollider.h"
#include "physics/components/rigidbody.h"
#include "time/time.h"
#include "rendering/components/sprite.h"
#include "rendering/renderer.h"
#include "rendering/graphics.h"
#include "rendering/colors.h"

namespace Game
{
    struct PlayerSettings
    {
        float speed = 80;
        float jumpForce = 120;

        int width = 10;
        int height = 10;
    };

    GameObject player;
    GameObject ground;

    PlayerSettings playerSettings;
    Rigidbody* playerRb = nullptr;

    void setupPlayer();
    void setupGround();

    void start()
    {
        setupPlayer();
        setupGround();
    }

    void update(float dt)
    {
        if (InputSystem::get().left)
            playerRb->velocity.x = -playerSettings.speed;
        else if (InputSystem::get().right)
            playerRb->velocity.x = playerSettings.speed;
        else
            playerRb->velocity.x = 0;

        if (InputSystem::get().up && playerRb->grounded)
        {
            playerRb->velocity.y = -playerSettings.jumpForce;
            playerRb->grounded = false;
        }
    }

    void setupPlayer()
    {
        player.transform->position = {75, 50};

        Sprite* sprite = player.addComponent<Sprite>();
        sprite->drawFunction = [sprite]()
        {
            int x = sprite->gameObject->transform->position.x;
            int y = sprite->gameObject->transform->position.y;

            Graphics::rect(x, y, 10, 10, Colors::WHITE, true);
            Graphics::rect(x + 2, y + 2, 2, 2, Colors::BLUE, true);
            Graphics::rect(x + 6, y + 2, 2, 2, Colors::BLUE, true);
            Graphics::rect(x + 2, y + 6, 6, 2, Colors::RED, true);
        };
        Renderer::registerSprite(sprite);

        BoxCollider* collider = player.addComponent<BoxCollider>();
        collider->width = playerSettings.width;
        collider->height = playerSettings.height;
        Solver::registerCollider(collider);

        playerRb = player.addComponent<Rigidbody>();
        player.rigidbody = playerRb;
    }

    void setupGround()
    {
        ground.transform->position = {0, 119};

        Sprite* sprite = ground.addComponent<Sprite>();
        sprite->drawFunction = [sprite]()
        {
            int x = sprite->gameObject->transform->position.x;
            int y = sprite->gameObject->transform->position.y;

            Graphics::rect(x, y, 160, 1, Colors::GREEN, true);
        };
        Renderer::registerSprite(sprite);

        BoxCollider* collider = ground.addComponent<BoxCollider>();
        collider->width = 160;
        collider->height = 1;
        Solver::registerCollider(collider);

        Rigidbody* rb = ground.addComponent<Rigidbody>();
        rb->settings.bodyType = Rigidbody::BodyType::Static;
        ground.rigidbody = rb;
    }
}
