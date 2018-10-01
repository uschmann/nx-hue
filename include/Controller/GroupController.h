#pragma once

#include "Controller/Controller.h"

class GroupController: public Controller {
    public:
        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);
        void onFrame(int deltaTime);
        void onRemove();
};