#include "View/NavBarButton.h"
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Utils.h"
#include "App.h"

NavBarButton::NavBarButton(int x, int y, const char* text) 
: View(x, y, 500, 70)
{
    mIsActive = false;
    mText = text;
}

void NavBarButton::onDraw(SDL_Renderer* renderer)
{
    if(mIsActive) {
        boxRGBA(renderer, mX, mY, mX + mWidth, mY + mHeight, 0xFF, 0xFF, 0xFF, 25);
    }

    TTF_Font* font = App::getInstance()->assetManager->regularFont;
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    Util_DrawText(renderer, mText, font, textColor, mX + 40, mY + (mHeight / 2) - 20);
}

bool NavBarButton::onEvent(SDL_Event* event)
{
    return false;
}

void NavBarButton::setActive(bool active)
{
    mIsActive = active;
}