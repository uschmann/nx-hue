#pragma once

#include "Controller/BaseController.h"
#include "Hue/Light.h"
#include "View/ColorWheel.h"
#include "View/ColorListener.h"
#include "View/ToggleButton.h"
#include "View/Slider.h"
#include "View/SliderChangeListener.h"

class LightDetailController: public BaseController, public ColorListener, public SliderChangeListener {
    public:
        LightDetailController(Light* light);
        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);
        void onColorChanged(int r, int g, int b);
        void onSliderValueChanged(float value);
    protected:
        Light* mLight;
        ColorWheel * mColorWheel;
        ToggleButton* mToggleButton;
        Slider* mSlider;
};