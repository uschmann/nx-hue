#pragma once

#include "View/View.h"
#include <SDL2/SDL.h>

class NavBarButton : public View
{
    public:
        NavBarButton(int x, int y, const char* text);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual bool onEvent(SDL_Event* event);

        void setActive(bool active);
    protected:
        bool mIsActive;
        const char* mText;
};