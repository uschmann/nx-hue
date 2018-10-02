#include "Controller/BaseController.h"


BaseController::BaseController() 
{

}
    
void BaseController::onCreate(App * app)
{
    Controller::onCreate(app);
    mActionBar = new ActionBar();
    mNavBar = new NavBar(0, 90);
}

bool BaseController::onEvent(SDL_Event * event)
{
    mNavBar->onEvent(event);
    return false;
}

void BaseController::onDraw(SDL_Renderer* renderer)
{
    mNavBar->onDraw(renderer);
    mActionBar->onDraw(renderer);
}