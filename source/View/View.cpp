#include "View/View.h"
#include <stdio.h>

View::View(int x, int y, int width, int height) 
{
    mX = x;
    mY = y;
    mWidth = width;
    mHeight = height;
}

void View::setX(int x) 
{
    mX = x;
    onLayout();
}

void View::setY(int y) 
{
    mY = y;
    onLayout();
}

void View::setWidth(int width)
{
    mWidth = width;
    onLayout();
}

void View::setHeight(int height)
{
    mHeight = height;
    onLayout();
}

int View::getX()
{
    return mX;
}

int View::getY()
{
    return mY;
}

int View::getWidth()
{
    return mWidth;
}

int View::getHeight()
{
    return mHeight;
}

bool View::isTapped(TapEvent* event)
{
    //return event->x >= mX && event->x <= mX + mWidth && 
    //event->y >= mY && event->y <= mY + mHeight;

    return isPointIn(event->x, event->y);
}

bool View::isPointIn(int x, int y)
{
    return x >= mX && x <= mX + mWidth && 
    y >= mY && y <= mY + mHeight;
}

void View::onDraw(SDL_Renderer* renderer) 
{
    
}

void View::onFrame(int deltaTime)
{

}

bool View::onEvent(SDL_Event* event)
{
    return false;
}

void View::onLayout()
{

}