#pragma once

#include "core/component.h"

class Transform : public Component
{
public:

    struct Position
    {
        float x = 0;
        float y = 0;
    };

    Position position;
};