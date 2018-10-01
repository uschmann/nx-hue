#include <stdio.h>
#include "Controller/GroupController.h"
#include "Event.h"

void GroupController::onCreate(App *app) {
    
}

bool GroupController::onEvent(SDL_Event * event) {
    if(event->type == SDL_USEREVENT) {
        TapEvent* e = (TapEvent*)event->user.data1;
        printf("EventCode: %d", event->user.code);
        printf("TAPPP! X: %d, Y: %d\n", e->x, e->y);
    }
    return false;
}

void GroupController::onDraw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0xa0, 0, 0, 0xFF);
    
}

void GroupController::onFrame(int deltaTime) {
    
}

void GroupController::onRemove() {
    
}

