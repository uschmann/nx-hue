#include <SDL2/SDL2_gfxPrimitives.h>
#include "Event.h"
#include "Utils.h"
#include "App.h"
#include "View/LightItem.h"
#include "App.h"
#include "Controller/LightDetailController.h"

LightItem::LightItem(Light* light,int x, int y)
: View(x, y, 700, 150)
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
    SDL_Color textColor2 = { 0xAA, 0xAA, 0xAA };
    TTF_Font* boldFont = App::getInstance()->assetManager->boldFont;
    TTF_Font* regularFont = App::getInstance()->assetManager->regularFont;
    
    Util_DrawText(renderer, mLight->name, boldFont, textColor, mX + 40, mY + (mHeight / 2 - 40));
    Util_DrawText(renderer, mLight->archetype, regularFont, textColor2, mX + 40, mY + (mHeight / 2 + 5));

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
        else if(isTapped(e)) {
            App::getInstance()->startController(new LightDetailController(mLight));
        }
    }
    return false;
}

void LightItem::onLayout()
{
    mToggleButton->setX(mX + mWidth - 100 - 40);
    mToggleButton->setY(mY + mHeight / 2 - 20);
}