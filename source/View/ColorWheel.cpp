#include "View/ColorWheel.h"
#include "App.h"
#include <stdio.h>
#include "Utils.h"
#include <SDL2/SDL2_gfxPrimitives.h>

ColorWheel::ColorWheel(int x, int y)
: View(x, y, 404, 404)
{
    mLastX = 0;
    mLastY = 0;
    mIsPicking = false;
    mColorListener = NULL;
}

void ColorWheel::onDraw(SDL_Renderer* renderer)
{
    SDL_Rect srcRect = { 0, 0, 404, 404 };
    SDL_Rect destRect = { mX, mY, mWidth, mHeight };

    SDL_Texture* colorWheel = App::getInstance()->assetManager->colorWheel;

    SDL_RenderCopy(renderer, colorWheel, &srcRect, &destRect);

    if(mLastX != 0) {
        filledCircleRGBA(renderer, mX + mLastX, mY + mLastY + 5, 40, 0, 0, 0, 50);
        filledCircleRGBA(renderer, mX + mLastX, mY + mLastY, 40, 0xFF, 0xFF, 0xFF, 0xFF);
        filledCircleRGBA(renderer, mX + mLastX, mY + mLastY, 30, mR, mG, mB, 0xFF);
    }
}

bool ColorWheel::onEvent(SDL_Event* event)
{
    Uint8 *p = 0;
    SDL_Surface* surface = App::getInstance()->assetManager->colorWheelSurface;
    int x = 0;
    int y = 0;
    int center = mHeight / 2;

    switch(event->type) {
        case SDL_FINGERDOWN:        
            
            x = ((int)(event->tfinger.x * 1280)) - mX;
            y = ((int)(event->tfinger.y * 720)) - mY;

            if(x >= 0 && y >= 0 && distance(x, y, 202, 202) <= 202) {
                mIsPicking = true;
                mLastX = x;
                mLastY = y;
                SDL_LockSurface(surface);
                p = (Uint8 *)((Uint8 *)(surface->pixels) + y * surface->pitch + x * 4);
                mR = p[0];
                mG = p[1];
                mB = p[2];
                SDL_UnlockSurface(surface);
            }
        break;
        case SDL_FINGERMOTION:
            if(mIsPicking) {
                x = ((int)(event->tfinger.x * 1280)) - mX;
                y = ((int)(event->tfinger.y * 720)) - mY;

                if(x >= 0 && y >= 0 && distance(x, y, 202, 202) <= 202) {
                    mLastX = x;
                    mLastY = y;
                    SDL_LockSurface(surface);
                    p = (Uint8 *)((Uint8 *)(surface->pixels) + y * surface->pitch + x * 4);
                    mR = p[0];
                    mG = p[1];
                    mB = p[2];
                    SDL_UnlockSurface(surface);
                }
            }
        break;
        case SDL_FINGERUP:
            if(mIsPicking && mColorListener != NULL) {
                mColorListener->onColorChanged(mR, mG, mB);
            }
            mIsPicking = false;
        break;
    }
    return false;
}

void ColorWheel::setColorListener(ColorListener* listener)
{
    mColorListener = listener;
}