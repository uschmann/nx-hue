#include "View/View.h"

View::View(int x, int y, int width, int height) 
{
    mRect = { x, y, width, height };
}

void View::setX(int x) 
{
    mRect.x = x;
}

void View::setY(int y) 
{
    mRect.y = y;
}

void View::setWidth(int width)
{
    mRect.w = width;
}

void View::setHeight(int height)
{
    mRect.h = height;
}

int View::getX()
{
    return mRect.x;
}

int View::getY()
{
    return mRect.y;
}

int View::getWidth()
{
    return mRect.w;
}

int View::getHeight()
{
    return mRect.h;
}

bool View::isTapped(TapEvent* event)
{
    return event->x >= mRect.x && event->x <= mRect.x + mRect.h && 
    event->y >= mRect.y && event->y <= mRect.y + mRect.h;
}

void View::onDraw(SDL_Renderer* renderer) 
{
    SDL_SetRenderDrawColor(renderer, 0x00, 0xff, 0x00, 0xff);
    SDL_RenderFillRect(renderer, &mRect);
}

void View::onFrame(int deltaTime)
{

}

bool View::onEvent(SDL_Event* event)
{
    return false;
}