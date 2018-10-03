#pragma once

#include "Controller/BaseController.h"
#include "Hue/Light.h"
#include "View/ColorWheel.h"
#include "View/ColorListener.h"

class LightDetailController: public BaseController, public ColorListener {
    public:
        LightDetailController(Light* light);
        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);
        void onColorChanged(int r, int g, int b);
    protected:
        Light* mLight;
        ColorWheel * mColorWheel;
};