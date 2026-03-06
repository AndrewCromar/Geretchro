#pragma once

struct Inputs
{
    bool up;
    bool down;
    bool left;
    bool right;
};

namespace InputSystem
{
    void setup();
    void update();
    const Inputs& get();
}