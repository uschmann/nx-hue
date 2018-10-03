#include "Controller/SettingsController.h"
#include "Utils.h"

void SettingsController::onCreate(App * app)
{
    BaseController::onCreate(app);

    mNavBar->mGroupsButton->setActive(false);
    mNavBar->mLightsButton->setActive(false);
    mNavBar->mSettingsButton->setActive(true);
}

bool SettingsController::onEvent(SDL_Event * event)
{
    BaseController::onEvent(event);

    return false;
}

void SettingsController::onDraw(SDL_Renderer* renderer)
{
    BaseController::onDraw(renderer);

    TTF_Font* boldFont = app->assetManager->boldFont;
    TTF_Font* font = app->assetManager->regularFont;

    int actionBarHeight = mActionBar->getHeight();
    int navBarWidth = mNavBar->getWidth();

    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    Util_DrawText(renderer, "About:", boldFont, textColor, navBarWidth + 40, actionBarHeight + 40);
    Util_DrawText(renderer, "Created by: Usch", font, textColor, navBarWidth + 40, actionBarHeight + 40 + 40);
}