#pragma once

class Collider;

namespace Solver
{
    struct PhysicsSettings
    {
        float gravity = 200.0f;
        int iterations = 4;
    };

    extern PhysicsSettings settings;

    void init();

    void registerCollider(class Collider* collider);

    void step(float dt);
}