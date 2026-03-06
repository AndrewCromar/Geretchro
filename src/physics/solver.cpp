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

void step()
{
}

}