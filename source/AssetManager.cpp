#include <stdio.h>
#include <SDL2/SDL_ttf.h>

#include "AssetManager.h"


bool AssetManager::load()
{
    regularFont = TTF_OpenFont("romfs:/OpenSans-Regular.ttf", 30);
    if(!regularFont) {
        printf("Could not load romfs:/OpenSans-Regular.ttf\n");
        return false;
    }

    boldFont = TTF_OpenFont("romfs:/OpenSans-Bold.ttf", 30);
    if(!boldFont) {
        printf("Could not load romfs:/OpenSans-Bold.ttf\n");
        return false;
    }

    return true;
}