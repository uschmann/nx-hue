#pragma once

#include <SDL2/SDL.h>

#include "View/View.h"
#include "View/ToggleButton.h"
#include "Hue/Group.h"

class GroupItem : public View
{
    public:
        GroupItem(Group* group,int x, int y);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual void onFrame(int deltaTime);
        virtual bool onEvent(SDL_Event* event);
    protected:
        Group* mGroup;
        ToggleButton* mToggleButton;
        void onLayout();
};