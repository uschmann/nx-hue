#include <SDL2/SDL2_gfxPrimitives.h>
#include "View/GroupItem.h"
#include "Event.h"
#include "App.h"
#include "Utils.h"

GroupItem::GroupItem(Group* group, int x, int y)
: View(x, y, 700, 100)
{
    mGroup = group;

    mToggleButton = new ToggleButton(mX + mWidth - 100 - 40, mY + mHeight / 2 - 20);
}

void GroupItem::onDraw(SDL_Renderer* renderer) 
{
    roundedBoxColor(renderer, mX, mY, mX + mWidth, mY + mHeight, 10, 0xFF292929);

    // Draw Name
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    TTF_Font* font =  App::getInstance()->assetManager->regularFont;
    Util_DrawText(renderer, mGroup->name, font, textColor, mX + 40, mY + (mHeight / 2 - 20));

    // Draw Toggle Button
    mToggleButton->onDraw(renderer);
}

void GroupItem::onFrame(int deltaTime)
{

}

bool GroupItem::onEvent(SDL_Event* event)
{
    if(event->type == SDL_USEREVENT) {
        TapEvent* e = (TapEvent*)event->user.data1;
        if(mToggleButton->isTapped(e)) {
            mToggleButton->setState(!mToggleButton->getState());
            App::getInstance()->hue->setGroupOnState(mGroup->id, mToggleButton->getState());
        }
        else if(this->isTapped(e)) {
            
        }
    }
    return false;
}

void GroupItem::onLayout()
{
    mToggleButton->setX(mX + mWidth - 100 - 40);
    mToggleButton->setY(mY + mHeight / 2 - 20);
}