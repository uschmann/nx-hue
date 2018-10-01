#pragma once

#include "View/View.h"
#include <SDL2/SDL.h>

class ToggleButton : public View
{
    public:
        ToggleButton(int x, int y);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual void onFrame(int deltaTime);
        virtual bool onEvent(SDL_Event* event);
    
        void setState(bool state);
        bool getState();

    protected:
        SDL_Rect mRect;
        bool mState;
};