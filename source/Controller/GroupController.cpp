#include <stdio.h>
#include "Controller/GroupController.h"
#include "Event.h"

void GroupController::onCreate(App *app) {
    this->app = app;
    mView = new ToggleButton(40, 40);
}

bool GroupController::onEvent(SDL_Event * event) {
    if(event->type == SDL_USEREVENT) {
        TapEvent* e = (TapEvent*)event->user.data1;
        printf("tap\n");
        if(mView->isTapped(e)) {
            mView->setState(!mView->getState());
            printf("TAPPP! X: %d, Y: %d\n", e->x, e->y);
        }
    }
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

