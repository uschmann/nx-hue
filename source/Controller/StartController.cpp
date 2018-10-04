#include "Controller/StartController.h"
#include "Controller/GroupController.h"
#include "FileSystem.h"
#include "Utils.h"

StartController::StartController() 
{
    mState = 0;
}
    
void StartController::onCreate(App * app)
{
    Controller::onCreate(app);
    mActionBar = new ActionBar();

    Hue* hue = app->hue;
    hue->discoverByMdns();
    if(!hue->hasIp()) {
        printf("No IP\n");
        char *ip = FileSystem::readTextFile("hueip.txt");
        if(ip != NULL) {
            printf("IP from FS: %s\n", ip);
            app->hue->setIp(ip);
            
            char * user = FileSystem::readTextFile("lightswitch.txt");
            if(user == NULL) {
                mState = StartController::STATE_NO_USER;
            }
            else {
                mState = StartController::STATE_REGISTER_COMPLETE;
                hue->setUser(user);
                app->startController(new GroupController());
            }
        }
        else {
            mState = STATE_NO_IP;
        }
    }
    else {
        char * user = FileSystem::readTextFile("lightswitch.txt");
        if(user == NULL) {
            mState = StartController::STATE_NO_USER;
        }
        else {
            mState = StartController::STATE_REGISTER_COMPLETE;
            hue->setUser(user);
            app->startController(new GroupController());
        }
    }
}

bool StartController::onEvent(SDL_Event * event)
{
    return false;
}

void StartController::onDraw(SDL_Renderer* renderer)
{
    mActionBar->onDraw(renderer);

    TTF_Font* boldFont = this->app->assetManager->boldFont;
    TTF_Font* regularFont = this->app->assetManager->regularFont;
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

    switch(mState) {
        case StartController::STATE_NO_IP:
            Util_DrawText(renderer, "Unable to find hue bridge.", boldFont, textColor, 40, mActionBar->getHeight() + 40);
        break;
        case StartController::STATE_NO_USER:
            Util_DrawText(renderer, "Please press the button on your hue bridge.", boldFont, textColor, 40, mActionBar->getHeight() + 40);
        break;
        case StartController::STATE_REGISTER_COMPLETE:
            Util_DrawText(renderer, "Setup complete!", boldFont, textColor, 40, mActionBar->getHeight() + 40);
        break;
    }
}

void StartController::onFrame(int deltaTime) 
{
    if(mState == StartController::STATE_NO_USER) {
        char* user = this->app->hue->registerUser();
        if(user != NULL) {
            FileSystem::writeTextFile("lightswitch.txt", user);
            app->hue->setUser(user);
            app->startController(new GroupController());
        }
        else {
            SDL_Delay(2000);
        }
    }
}