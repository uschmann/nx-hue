#include "View/ToggleButton.h"
#include <stdio.h>

ToggleButton::ToggleButton(int x, int y)
: View(x, y, 80,  40)
{
        mState = false;
}

void ToggleButton::onDraw(SDL_Renderer* renderer)
{
        if(mState) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, 0xFF);
        }
        else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0xFF, 0xFF);
        }

        SDL_Rect rect = {
                mX,
                mY,
                mWidth,
                mHeight
        };
        SDL_RenderFillRect(renderer, &rect);
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