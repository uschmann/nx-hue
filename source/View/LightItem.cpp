#include <SDL2/SDL2_gfxPrimitives.h>
#include "Event.h"
#include "Utils.h"
#include "App.h"
#include "View/LightItem.h"

LightItem::LightItem(Light* light,int x, int y)
: View(x, y, 700, 100)
{
    mLight = light;

    mToggleButton = new ToggleButton(mX + mWidth - 100 - 40, mY + mHeight / 2 - 20);
    mToggleButton->setState(mLight->state->on);
}

void LightItem::onDraw(SDL_Renderer* renderer)
{
    roundedBoxColor(renderer, mX, mY, mX + mWidth, mY + mHeight, 10, 0xFF292929);

    // Draw Name
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    TTF_Font* font =  App::getInstance()->assetManager->regularFont;
    Util_DrawText(renderer, mLight->name, font, textColor, mX + 40, mY + (mHeight / 2 - 20));

    // Draw Toggle Button
    mToggleButton->onDraw(renderer);
}

void LightItem::onFrame(int deltaTime)
{

}

bool LightItem::onEvent(SDL_Event* event)
{
    if(event->type == SDL_USEREVENT) {
        TapEvent* e = (TapEvent*)event->user.data1;
        if(mToggleButton->isTapped(e)) {
            mLight->state->on = !mLight->state->on;
            mToggleButton->setState(mLight->state->on);
            App::getInstance()->hue->setOnState(mLight->id, mLight->state->on);
        }
    }
    return false;
}