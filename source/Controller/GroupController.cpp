#include <stdio.h>
#include "Controller/GroupController.h"
#include "Event.h"

void GroupController::onCreate(App *app) {
    this->app = app;
    

    mGroups = this->app->hue->getGroups();
    
    mView = new GroupItem(&mGroups->at(0), 40, 40);
}

bool GroupController::onEvent(SDL_Event * event) {
    mView->onEvent(event);
    return false;
}

void GroupController::onDraw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xa0, 0, 0, 0xFF);
    mView->onDraw(renderer);
}

void GroupController::onFrame(int deltaTime) {
    
}

void GroupController::onRemove() {
    
}

