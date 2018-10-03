#include "Controller/LightDetailController.h"
#include "Utils.h"

LightDetailController::LightDetailController(Light* light)
{
    mLight = light;
}

void LightDetailController::onCreate(App * app)
{
    BaseController::onCreate(app);

    mColorWheel = new ColorWheel(mNavBar->getWidth() + 40, mActionBar->getHeight() + 110);
    mColorWheel->setColorListener(this);
}

bool LightDetailController::onEvent(SDL_Event * event)
{
    BaseController::onEvent(event);
    mColorWheel->onEvent(event);
    return false;
}

void LightDetailController::onDraw(SDL_Renderer* renderer)
{
    BaseController::onDraw(renderer);

    TTF_Font* boldFont = app->assetManager->boldFont;
    TTF_Font* regularFont = app->assetManager->regularFont;

    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

    Util_DrawText(renderer, mLight->name, boldFont, textColor, mNavBar->getWidth() + 40, mActionBar->getHeight() + 40);

    mColorWheel->onDraw(renderer);
}

void LightDetailController::onColorChanged(int r, int g, int b)
{
    app->hue->setColorRgb(mLight->id, r, g, b);
}