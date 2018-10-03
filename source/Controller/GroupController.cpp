#include <stdio.h>
#include "Controller/GroupController.h"
#include "Event.h"

void GroupController::onCreate(App *app) {
    BaseController::onCreate(app);

    mNavBar->mGroupsButton->setActive(true);
    mNavBar->mLightsButton->setActive(false);    
    mNavBar->mSettingsButton->setActive(false);

    mGroups = this->app->hue->getGroups();
    
    mScrollView = new ScrollView(
        mNavBar->getWidth() + 40, 
        mActionBar->getHeight() + 40, 
        1280 - mNavBar->getWidth() - 80,
        720 - mActionBar->getHeight() - 40
    );

    for(int i = 0; i < mGroups->size(); i++)
    {
        mScrollView->addChild(new GroupItem(&mGroups->at(i), 0, 0));
    }
}

bool GroupController::onEvent(SDL_Event * event) {
    BaseController::onEvent(event);
    mScrollView->onEvent(event);
    return false;
}

void GroupController::onDraw(SDL_Renderer* renderer) {
    BaseController::onDraw(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0xa0, 0, 0, 0xFF);
    mScrollView->onDraw(renderer);
}

void GroupController::onFrame(int deltaTime) {
    
}

void GroupController::onRemove() {
    
}

