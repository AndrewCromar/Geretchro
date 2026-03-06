#pragma once

#include <vector>
#include "component.h"
#include "transform.h"
#include "rendering/components/sprite.h"

class GameObject
{
public:

    Transform* transform;

    GameObject()
    {
        transform = addComponent<Transform>();
    }

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

    void draw()
    {
        for (Component* c : components)
        {
            Sprite* sprite = dynamic_cast<Sprite*>(c);

            if (sprite && sprite->draw)
                sprite->draw();
        }
    }

private:
    std::vector<Component*> components;
};