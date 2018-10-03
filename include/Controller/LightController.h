#pragma once

#include "Controller/BaseController.h"
#include "Hue/Light.h"
#include <vector>
#include "View/LightItem.h"
#include "View/ScrollView.h"

class LightController: public BaseController {
    public:
        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);
    protected:
        vector<Light>* mLights;
        ScrollView* mScrollView;
};