#pragma once
#include "Controller/Controller.h"
#include "View/ActionBar.h"
#include "View/NavBar.h"

class StartController: public Controller 
{
    public:
        StartController();
        void onCreate(App * app);
        bool onEvent(SDL_Event * event);
        void onDraw(SDL_Renderer* renderer);
        void onFrame(int deltaTime);
    protected:
        ActionBar* mActionBar;
        int mState;

        static const int STATE_NO_IP = 1;
        static const int STATE_NO_USER = 2;
        static const int STATE_REGISTER_COMPLETE = 3;
};