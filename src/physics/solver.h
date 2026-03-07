#pragma once

class Collider;

namespace Solver
{
    void init();

    void registerCollider(class Collider* collider);

    void step();
}