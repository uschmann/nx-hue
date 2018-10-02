#pragma once

#include "View/View.h"
#include <SDL2/SDL.h>

class NavBar : public View
{
    public:
        NavBar(int x, int y);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual bool onEvent(SDL_Event* event);
};