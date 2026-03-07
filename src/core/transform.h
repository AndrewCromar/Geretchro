#pragma once

#include "core/component.h"
#include "core/math/vectors.h"

class Transform : public Component
{
public:
    Math::Vector2 position;
};