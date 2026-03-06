#include "renderer.h"
#include "rendering/components/sprite.h"

#include <vector>

namespace Renderer
{

static std::vector<::Sprite*> sprites;

void register_sprite(::Sprite* sprite)
{
    sprites.push_back(sprite);
}

void draw()
{
    for(::Sprite* s : sprites)
    {
        s->draw();
    }
}

}