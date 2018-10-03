#pragma once

#include "Controller/BaseController.h"
#include <vector>

class SettingsController: public BaseController {
    public:
        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);
};