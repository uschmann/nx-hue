#include "View/NavBar.h"


NavBar::NavBar(int x, int y)
: View(x, y, 500, 720 -90)
{

}

void NavBar::onDraw(SDL_Renderer* renderer)
{
    SDL_Rect bgRect = { mX, mY, mWidth, mHeight };
    SDL_SetRenderDrawColor(renderer, 20, 49, 100, 0xFF);
    SDL_RenderFillRect(renderer, &bgRect);
}

bool NavBar::onEvent(SDL_Event* event)
{

}