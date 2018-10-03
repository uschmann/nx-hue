#pragma once

#include "View/View.h"
#include <SDL2/SDL.h>

class IconButton : public View
{
    public:
        IconButton(SDL_Texture* icon, int x, int y);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual bool onEvent(SDL_Event* event);

        void setActive(bool active);
    protected:
        SDL_Texture* mIcon;
        bool mIsActive;
};