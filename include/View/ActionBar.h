#pragma once

#include "View/View.h"
#include <SDL2/SDL.h>

class ActionBar : public View
{
    public:
        ActionBar();

        virtual void onDraw(SDL_Renderer* renderer);
        virtual bool onEvent(SDL_Event* event);
};