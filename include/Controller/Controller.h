#pragma once

#include <SDL2/SDL.h>
#include "App.h"

class Controller {
    public:
        virtual void onCreate(App * app);
        virtual bool onEvent(SDL_Event * event);
        virtual void onDraw(SDL_Renderer* renderer);
        virtual void onFrame(int deltaTime);
        virtual void onRemove();
    protected:
        App * app;
};
