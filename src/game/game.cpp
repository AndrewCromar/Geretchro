#include "game.h"
#include <Arduino.h>
#include "../time/time.h"
#include "../core/gameobject.h"

namespace Game
{
    GameObject player;

    void start()
    {
        player.transform->x = 0;
        player.transform->y = 0;
    }

    void update(float dt)
    {

    }
}
