#include "View/IconButton.h"
#include <SDL2/SDL2_gfxPrimitives.h>

const int SIZE = 90;

IconButton::IconButton(SDL_Texture* icon, int x, int y)
: View(x, y, SIZE, SIZE)
{
    mIcon = icon;
    mIsActive = false;
}

void IconButton::onDraw(SDL_Renderer* renderer)
{
    if(mIsActive) {
        int radius = (SIZE / 2) + 8;
        filledCircleRGBA(renderer, mX + radius - 8, mY + radius - 8, radius, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    filledCircleRGBA(renderer, mX + SIZE / 2, mY + SIZE / 2, SIZE / 2, 41, 41, 41, 0xFF);

    if(mIcon != NULL) {
        SDL_Rect srcRect = { 0, 0, 50, 50};
        SDL_Rect destRect = { mX + SIZE / 2 - 25, mY + SIZE / 2 - 25, 50, 50};

        SDL_RenderCopy(renderer, mIcon, &srcRect, &destRect);
    }
}

void IconButton::setActive(bool active)
{
    mIsActive = active;
}

bool IconButton::onEvent(SDL_Event* event)
{
    return false;
}