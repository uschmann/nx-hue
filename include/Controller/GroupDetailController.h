#pragma once

#include "Controller/BaseController.h"
#include "View/GroupItem.h"
#include "View/ScrollView.h"
#include "View/IconButton.h"
#include "Hue/Group.h"
#include "Hue/Light.h"
#include <vector>
#include "View/Slider.h"
#include "View/SliderChangeListener.h"
#include "View/ColorWheel.h"
#include "View/ColorListener.h"

class GroupDetailController: public BaseController, public SliderChangeListener, public ColorListener {
    public:
        GroupDetailController(char* groupId);

        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);
        
        void onColorChanged(int r, int g, int b);
        void onSliderValueChanged(float value);
    protected:
        ScrollView* mLightsScrollView;
        char* mGroupId;
        Group* mGroup;

        IconButton* mLightButton;
        IconButton* mSettingsButton;
        ColorWheel* mColorWheel;
        Slider* mSlider;
        
        int mState;      
};  