#include "solver.h"
#include "physics/components/collider.h"
#include "physics/components/boxCollider.h"

#include <vector>

namespace Solver
{

static std::vector<::Collider*> colliders;

void register_collider(::Collider* collider)
{
    colliders.push_back(collider);
}

struct Vector2
{
    float x;
    float y;
};

void solve_collisions();
Vector2 get_bounding_box_overlap(const Collider::BoundingBox& a, const Collider::BoundingBox& b);
void move_object(Vector2 overlap, Collider* colA, Collider* colB);

void step()
{
    solve_collisions();
}

void solve_collisions()
{
    for (const auto& collider : colliders)
    {
        auto boxA = collider->get_bounding_box();

        for (const auto& other : colliders)
        {
            if (collider == other)
                continue;

            auto boxB = other->get_bounding_box();

            Vector2 overlap = get_bounding_box_overlap(boxA, boxB);

            if (overlap.x > 0 && overlap.y > 0)
            {
                move_object(overlap, collider, other);
            }
        }
    }
}

Vector2 get_bounding_box_overlap(const Collider::BoundingBox& a, const Collider::BoundingBox& b)
{
    float overlapX = std::max(0.0f, std::min(a.x + a.width, b.x + b.width) - std::max(a.x, b.x));
    float overlapY = std::max(0.0f, std::min(a.y + a.height, b.y + b.height) - std::max(a.y, b.y));

    return {overlapX, overlapY};
}

void move_object(Vector2 overlap, Collider* colA, Collider* colB)
{
    if (overlap.x < overlap.y)
    {
        float halfOverlapX = overlap.x / 2.0f;

        if (colA->gameObject->transform->position.x < colB->gameObject->transform->position.x)
        {
            colA->gameObject->transform->position.x -= halfOverlapX;
            colB->gameObject->transform->position.x += halfOverlapX;
        }
        else
        {
            colA->gameObject->transform->position.x += halfOverlapX;
            colB->gameObject->transform->position.x -= halfOverlapX;
        }
    }
    else
    {
        float halfOverlapY = overlap.y / 2.0f;

        if (colA->gameObject->transform->position.y < colB->gameObject->transform->position.y)
        {
            colA->gameObject->transform->position.y -= halfOverlapY;
            colB->gameObject->transform->position.y += halfOverlapY;
        }
        else
        {
            colA->gameObject->transform->position.y += halfOverlapY;
            colB->gameObject->transform->position.y -= halfOverlapY;
        }
    }
}

}