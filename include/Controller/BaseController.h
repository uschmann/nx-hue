#pragma once
#include "Controller/Controller.h"
#include "View/ActionBar.h"
#include "View/NavBar.h"

class BaseController: public Controller 
{
    public:
        BaseController();
        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);

    protected:
        NavBar* mNavBar;
        ActionBar* mActionBar;
};