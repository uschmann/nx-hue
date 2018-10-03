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
    TTF_Font* font = App::getInstance()->assetManager->boldFont;

    SDL_Rect srcRect = { 0, 0, 1, 5};
    SDL_Rect destRect = { mX, mY + mHeight, mWidth, 5};
    SDL_RenderCopy(renderer, App::getInstance()->assetManager->shadow, &srcRect, &destRect);


    Util_DrawText(renderer, "Light|Switch", font, textColor, 40, 25);
}

bool ActionBar::onEvent(SDL_Event* event)
{
    return false;
}