#pragma once

#include "View/View.h"
#include <SDL2/SDL.h>
#include <vector>

using std::vector;

class ScrollView : public View
{
    public:
        ScrollView(int x, int y, int width, int height);

        virtual void onDraw(SDL_Renderer* renderer);
        virtual bool onEvent(SDL_Event* event);

        void addChild(View* view);
        void setPadding(int padding);
    protected:
        vector<View*>* mChilds;
        int mPadding;
        int mScrollY;
        int mMaxScrollY;
        bool mIsScrolling;
        void layoutChilds();
};