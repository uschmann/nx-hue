#pragma once

#include "Controller/BaseController.h"
#include "View/GroupItem.h"
#include "View/ScrollView.h"
#include "Hue/Group.h"
#include "Hue/Light.h"
#include <vector>

class GroupDetailController: public BaseController {
    public:
        GroupDetailController(char* groupId);

        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);
    protected:
        ScrollView* mLightsScrollView;
        char* mGroupId;
        Group* mGroup;
};