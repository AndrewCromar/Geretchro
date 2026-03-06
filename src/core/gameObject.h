#pragma once

#include <vector>
#include "component.h"

class GameObject
{
public:

    template <typename T>
    T* addComponent()
    {
        T* component = new T();
        component->gameObject = this;

        components.push_back(component);

        component->start();

        return component;
    }

    void update(float dt)
    {
        for (Component* c : components)
        {
            c->update(dt);
        }
    }

private:
    std::vector<Component*> components;
};