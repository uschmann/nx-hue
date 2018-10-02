#include "View/ActionBar.h"
#include "Utils.h"
#include "App.h"

ActionBar::ActionBar()
:View (0, 0, 1280, 90)
{

}

void ActionBar::onDraw(SDL_Renderer* renderer)
{
    SDL_Rect bgRect = { mX, mY, mWidth, mHeight };
    SDL_SetRenderDrawColor(renderer, 31, 64, 123, 0xFF);
    SDL_RenderFillRect(renderer, &bgRect);

    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    TTF_Font* font = App::getInstance()->assetManager->regularFont;


    Util_DrawText(renderer, "Hue-NX", font, textColor, 40, 25);
}

bool ActionBar::onEvent(SDL_Event* event)
{
    return false;
}