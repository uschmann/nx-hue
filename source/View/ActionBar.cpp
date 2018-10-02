#include "View/ActionBar.h"


ActionBar::ActionBar()
:View (0, 0, 1280, 90)
{

}

void ActionBar::onDraw(SDL_Renderer* renderer)
{
    SDL_Rect bgRect = { mX, mY, mWidth, mHeight };
    SDL_SetRenderDrawColor(renderer, 31, 64, 123, 0xFF);
    SDL_RenderFillRect(renderer, &bgRect);
}

bool ActionBar::onEvent(SDL_Event* event)
{
    return false;
}