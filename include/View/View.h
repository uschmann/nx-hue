#pragma once

#include "Event.h"
#include <SDL2/SDL.h>

class View
{
    public:
        View(int x, int y, int width, int height);
        void setX(int x);
        void setY(int y);
        void setWidth(int width);
        void setHeight(int height);

        int getX();
        int getY();
        int getWidth();
        int getHeight();

        bool isTapped(TapEvent* event);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual void onFrame(int deltaTime);
        virtual bool onEvent(SDL_Event* event);
    
    protected:
        SDL_Rect mRect;
};