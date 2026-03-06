#pragma once

#include "core/component.h"

class Collider : public Component
{
public:
    struct BoundingBox
    {
        float x;
        float y;
        float width;
        float height;
    };

    virtual BoundingBox get_bounding_box() const = 0;

    virtual ~Collider() = default;
};