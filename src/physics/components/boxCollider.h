#pragma once
#include "collider.h"
#include "core/gameObject.h"

class BoxCollider : public Collider
{
public:
    float width = 10;
    float height = 10;

    BoundingBox get_bounding_box() const override
    {
        return {
            gameObject->transform->position.x,
            gameObject->transform->position.y,
            width,
            height
        };
    }
};