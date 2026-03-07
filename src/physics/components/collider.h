#pragma once

#include "core/component.h"
#include "core/math/vectors.h"

class Collider : public Component
{
public:
    virtual Math::Vector4 getBoundingBox() const = 0;

    virtual ~Collider() = default;
};