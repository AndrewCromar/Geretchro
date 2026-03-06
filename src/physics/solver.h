#pragma once

class Collider;

namespace Solver
{
    void init();

    void register_collider(class Collider* collider);

    void step();
}