#pragma once 


#include <switch.h>
#include <Hue/Hue.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <AssetManager.h>

class Controller;

class App {
    public:
        Hue * hue;
        AssetManager * assetManager;
        static App *getInstance();
        bool init();
        void startController(Controller * controller);
        void run();
    protected:
        App();
        static App * INSTANCE; 
        bool isRunning;
        Uint32 lastMouseDown;
        Controller * controller;
        int mLastTick;

        SDL_Window* mWindow;
        SDL_Renderer* mRenderer;
        SDL_Surface* mScreen;
};
