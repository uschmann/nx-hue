#include "View/ToggleButton.h"
#include <stdio.h>
#include "App.h"

ToggleButton::ToggleButton(int x, int y)
: View(x, y, 100,  50)
{
        mState = false;
}

void ToggleButton::onDraw(SDL_Renderer* renderer)
{
        SDL_Rect srcRect = { 0, 0, 100, 50 };
        if(mState) {
                srcRect.y = 50;
        }

        

        SDL_Rect rect = {
                mX,
                mY,
                mWidth,
                mHeight
        };
        SDL_RenderCopy(renderer, App::getInstance()->assetManager->toggleButton, &srcRect, &rect);
}

void ToggleButton::onFrame(int deltaTime)
{

}

bool ToggleButton::onEvent(SDL_Event* event)
{
        return false;
}

void ToggleButton::setState(bool state)
{
        mState = state;
}

bool ToggleButton::getState()
{
        return mState;
}