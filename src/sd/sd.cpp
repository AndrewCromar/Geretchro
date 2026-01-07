#include "sd.h"
#include "../graphics/graphicsengine.h"
#include "../graphics/colors.h"

bool sd_in = false;

void setup_sd()
{
    if (SD.begin(SD_CS))
    {
        sd_in = true;
    }
}