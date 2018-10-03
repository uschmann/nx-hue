#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "AssetManager.h"


bool AssetManager::load(SDL_Renderer* renderer)
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

    toggleButton = IMG_LoadTexture(renderer ,"romfs:/switch.png");
    if (!toggleButton) {
        printf("Could not load romfs:/switch.png\n");
        return false;
    }

    colorWheel = IMG_LoadTexture(renderer ,"romfs:/colorwheel.png");
    if (!colorWheel) {
        printf("Could not load romfs:/colorwheel.png\n");
        return false;
    }
    colorWheelSurface = IMG_Load("romfs:/colorwheel.png");
    if(!colorWheelSurface) {
        printf("Could not load romfs:/colorwheel.png to surface\n");
        return false;
    }

    return true;
}