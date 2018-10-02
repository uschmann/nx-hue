#pragma once

#include "Controller/BaseController.h"
#include "View/GroupItem.h"
#include "Hue/Group.h"
#include <vector>

class GroupController: public BaseController {
    public:
        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);
        void onFrame(int deltaTime);
        void onRemove();
    protected:
        GroupItem* mView;
        vector<Group>* mGroups;
};