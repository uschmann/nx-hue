#include <SDL2/SDL2_gfxPrimitives.h>
#include "View/Slider.h"

const int HANDLE_RADIUS = 20;
const int HEIGHT = 40;

Slider::Slider(int x, int y, int width)
: View(x, y, width, HEIGHT)
{
    mHandleX = 0;
    mValue = 0;
    mIsPicking = false;
}

void Slider::onDraw(SDL_Renderer* renderer)
{   
    roundedBoxRGBA(renderer, mX, mY + HEIGHT / 2 - 4 , mX + mWidth, mY + HEIGHT / 2  + 4, 2, 44, 70, 116, 0xFF);

    filledCircleRGBA(renderer, mX + mHandleX, mY + HEIGHT / 2 + 5, HANDLE_RADIUS, 0, 0, 0, 30);
    filledCircleRGBA(renderer, mX + mHandleX, mY + HEIGHT / 2, HANDLE_RADIUS, 54, 94, 165, 0xFF);
}

bool Slider::onEvent(SDL_Event* event)
{
    int x = 0;

    switch(event->type) {
        case SDL_FINGERDOWN:        
            if(isPointIn(((int)(event->tfinger.x * 1280)), ((int)(event->tfinger.y * 720)))) {
                mIsPicking = true;
                mHandleX = ((int)(event->tfinger.x * 1280)) - mX;
            }
        break;
        case SDL_FINGERMOTION:
            if(mIsPicking) {
                x = ((int)(event->tfinger.x * 1280)) - mX;

                if(x < 0) {
                    x = 0;
                }

                if(x > mWidth)
                {
                    x = mWidth;
                }
                mHandleX = x;
            }
        break;
        case SDL_FINGERUP:
            if(mIsPicking && mListener != NULL) {
                calculateValue();
                mListener->onSliderValueChanged(mValue);
            }
            mIsPicking = false;
        break;
    }
    return false;
}

void Slider::setSliderChangeListener(SliderChangeListener* listener)
{
    mListener = listener;
}

void Slider::setValue(float value)
{
    if(value < 0) {
        value = 0;
    }

    if(value > 1)
    {
        value = 1;
    }

    mValue = value;
    calculateHandleX();
}

void Slider::calculateValue()
{
    mValue = ((float)mHandleX) / ((float)mWidth);
}

void Slider::calculateHandleX()
{
    mHandleX = mValue * ((float)mWidth);
}