#include <stdio.h>
#include "Controller/GroupController.h"
#include "Event.h"

void GroupController::onCreate(App *app) {
    BaseController::onCreate(app);

    mNavBar->mGroupsButton->setActive(true);
    mNavBar->mLightsButton->setActive(false);    
    mNavBar->mSettingsButton->setActive(false);

    mGroups = this->app->hue->getGroups();
    
    mView = new GroupItem(&mGroups->at(0), mNavBar->getWidth() + 40, mActionBar->getHeight() + 40);
}

bool GroupController::onEvent(SDL_Event * event) {
    BaseController::onEvent(event);
    mView->onEvent(event);
    return false;
}

void GroupController::onDraw(SDL_Renderer* renderer) {
    BaseController::onDraw(renderer);
    
    SDL_SetRenderDrawColor(renderer, 0xa0, 0, 0, 0xFF);
    mView->onDraw(renderer);
}

void GroupController::onFrame(int deltaTime) {
    
}

void GroupController::onRemove() {
    
}

