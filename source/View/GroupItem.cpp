
#include "View/GroupItem.h"
#include "Event.h"
#include "App.h"

GroupItem::GroupItem(Group* group, int x, int y)
: View(x, y, 400, 100)
{
    mGroup = group;

    mToggleButton = new ToggleButton(mX + mWidth - 100, mY + mHeight / 2 - 20);
}

void GroupItem::onDraw(SDL_Renderer* renderer) 
{
    SDL_Rect bgRect = { mX, mY, mWidth, mHeight };
    SDL_SetRenderDrawColor(renderer, 0x33, 0x33, 0x33, 0xFF);
    SDL_RenderFillRect(renderer, &bgRect);

    // Draw Name
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(App::getInstance()->assetManager->regularFont, mGroup->name, textColor);
    SDL_Rect textRect = { mX + 20, mY + (mHeight / 2 -surfaceMessage->h / 2), surfaceMessage->w, surfaceMessage->h };
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(texture);

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