#include "View/ScrollView.h"

ScrollView::ScrollView(int x, int y, int width, int height)
: View(x, y, width, height)
{
    mChilds = new vector<View*>;
    mPadding = 40;
    mScrollY = 0;
    mIsScrolling = false;
}

void ScrollView::onDraw(SDL_Renderer* renderer)
{
    SDL_Rect rect = { mX, mY, mWidth, mHeight };
    SDL_RenderSetClipRect(renderer, &rect);
    for(int i = 0; i < mChilds->size(); i++) {
        mChilds->at(i)->onDraw(renderer);
    }
    SDL_RenderSetClipRect(renderer, NULL);
}

bool ScrollView::onEvent(SDL_Event* event)
{
    switch(event->type)
    {
        case SDL_FINGERDOWN:
            if(isPointIn(event->tfinger.x * 1280, event->tfinger.y * 720)) {
                mIsScrolling = true;
            }
        break;
        case SDL_FINGERUP:
            mIsScrolling = false;
        break;    
        case SDL_FINGERMOTION:
            if(mIsScrolling) {
                mScrollY += event->tfinger.dy * 720;
                if(mScrollY < mMaxScrollY) {
                    mScrollY = mMaxScrollY;
                }

                if(mScrollY > 0) {
                    mScrollY = 0;
                }
                layoutChilds();
            }
        break;
    }

    for(int i = 0; i < mChilds->size(); i++) {
        mChilds->at(i)->onEvent(event);
    }
    return false;
}

void ScrollView::addChild(View* view)
{
    mChilds->push_back(view);
    layoutChilds();
}

void ScrollView::setPadding(int padding)
{
    mPadding = padding;
}

void ScrollView::layoutChilds()
{
    int currentY = mY + mScrollY;
    for(int i = 0; i < mChilds->size(); i++) {
        View* child = mChilds->at(i);
        child->setX(mX);
        child->setY(currentY);
        currentY += child->getHeight() + mPadding;
    }
    mMaxScrollY = currentY * -1;
}