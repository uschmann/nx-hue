#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "App.h"
#include "Controller/Controller.h"
#include "Event.h"

#define DEBUG

App *App::INSTANCE = 0;

App::App() {
    this->isRunning = false;
    this->hue = new Hue();
    this->assetManager = new AssetManager();
    this->controller = NULL;
    mLastTick = 0;
}

App * App::getInstance() {
    if(!App::INSTANCE) {
        App::INSTANCE = new App();
    }
    return App::INSTANCE;
}

bool App::init() {
  SDL_Init(SDL_INIT_EVERYTHING);

  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  SDL_JoystickEventState(SDL_ENABLE);
  SDL_JoystickOpen(0);
  TTF_Init();

  romfsInit();

  #ifdef DEBUG
  socketInitializeDefault();
  nxlinkStdio();
  printf("printf output now goes to nxlink server\n");
  #endif // DEBUG

  mWindow = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
  if (!mWindow) {
    printf("SDL_CreateWindow() failed!\n");
    SDL_Quit();
    return false;
  }

  mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_SOFTWARE);
  if (!mRenderer) {
    printf("SDL_CreateRenderer() failed!\n");
    SDL_Quit();
    return false;
  }

  mScreen = SDL_GetWindowSurface(mWindow);
  if (!mScreen) {
    printf("SDL_GetWindowSurface() failed!\n");
    SDL_Quit();
    return false;
  }

  this->assetManager->load();

  printf("Init success\n");

  return true;
}

void App::run() {
    this->isRunning = true;
    SDL_Event event;
    mLastTick = SDL_GetTicks();

    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);

    while (this->isRunning)
	{	
        int currentTick = SDL_GetTicks();
        int deltaTime = currentTick - mLastTick;
        mLastTick = currentTick;
        
		while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_FINGERDOWN:
                    this->lastMouseDown = SDL_GetTicks();
                    break;
                case SDL_FINGERUP:
                    if((SDL_GetTicks() - this->lastMouseDown) < 200) {
                        TapEvent tapEvent;
                        tapEvent.x = ((int)(event.tfinger.x * 1280));
                        tapEvent.y = ((int)(event.tfinger.y * 720));

                        SDL_Event event;
                        event.type = SDL_USEREVENT;
                        event.user.code = EVENT_TAP; // TODO use constant
                        event.user.data1 = &tapEvent;
                        SDL_PushEvent(&event);
                    }
                    break;
                case SDL_JOYBUTTONDOWN:
                    switch(event.jbutton.button) {
                        case SDL_CONTROLLER_BUTTON_A:
                        
                        break;
                        case SDL_CONTROLLER_BUTTON_X:
                            isRunning = false;
                        break;
                    }
                    break;
            }

            if(this->controller != NULL) {
                this->controller->onEvent(&event);
            }
        }
        
        if(this->controller != NULL) {
            this->controller->onFrame(deltaTime);
        }

        SDL_RenderClear(mRenderer);
        if(this->controller != NULL) {
            this->controller->onDraw(mRenderer);
        }
		SDL_RenderPresent(mRenderer);
	}
    
    #ifdef DEBUG
        socketExit();
    #endif // DEBUG

    SDL_Quit();
}

void App::startController(Controller * controller) {
    if(this->controller != NULL) {
        this->controller->onRemove();
        delete this->controller;
    }
    
    this->controller = controller;
    this->controller->onCreate(this);
    this->controller->onDraw(mRenderer);
}