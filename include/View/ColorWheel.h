#pragma once

#include "View/View.h"
#include <SDL2/SDL.h>
#include "View/ColorListener.h"

class ColorWheel : public View
{
    public:
        ColorWheel(int x, int y);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual bool onEvent(SDL_Event* event);

        void setColorListener(ColorListener* listener);
    protected:
        int mLastX;
        int mLastY;
        int mR;
        int mG;
        int mB;
        bool mIsPicking;
        ColorListener* mColorListener;
};