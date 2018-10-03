#pragma once

#include <SDL2/SDL.h>

#include "View/View.h"
#include "View/ToggleButton.h"
#include "Hue/Light.h"

class LightItem : public View
{
    public:
        LightItem(Light* light,int x, int y);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual void onFrame(int deltaTime);
        virtual bool onEvent(SDL_Event* event);
    protected:
        Light* mLight;
        ToggleButton* mToggleButton;
        void onLayout();
};