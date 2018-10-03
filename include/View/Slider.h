#pragma once

#include "View/View.h"
#include "View/SliderChangeListener.h"
#include <SDL2/SDL.h>

class Slider : public View
{
    public:
        Slider(int x, int y, int width);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual bool onEvent(SDL_Event* event);
        void setValue(float value);
        void setSliderChangeListener(SliderChangeListener* listener);
    protected:
        float mValue;
        int mHandleX;
        bool mIsPicking;
        SliderChangeListener* mListener;

        void calculateValue();
        void calculateHandleX();
};