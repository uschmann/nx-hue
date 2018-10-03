#include "Controller/LightDetailController.h"
#include "Utils.h"

LightDetailController::LightDetailController(Light* light)
{
    mLight = light;
}

void LightDetailController::onCreate(App * app)
{
    BaseController::onCreate(app);

    mColorWheel = new ColorWheel(mNavBar->getWidth() + 40 + 350 - 220, mActionBar->getHeight() + 110);
    mColorWheel->setColorListener(this);

    mToggleButton = new ToggleButton(1280 - 100 -40, mActionBar->getHeight() + 40);
    mToggleButton->setState(mLight->state->on);

    mSlider = new Slider(mNavBar->getWidth() + 80, 720 - 80 , 1280 - (mNavBar->getWidth() + 160));
    mSlider->setSliderChangeListener(this);
    mSlider->setValue(mLight->state->bri / 254.f);
}

bool LightDetailController::onEvent(SDL_Event * event)
{
    BaseController::onEvent(event);
    mColorWheel->onEvent(event);
    mSlider->onEvent(event);

    if(event->type == SDL_USEREVENT) {
        TapEvent* e = (TapEvent*)event->user.data1;
        if(mToggleButton->isTapped(e)) {
            mLight->state->on = !mLight->state->on;
            mToggleButton->setState(mLight->state->on);
            app->hue->setOnState(mLight->id, mLight->state->on);
        }
    }

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
    mToggleButton->onDraw(renderer);
    mSlider->onDraw(renderer);
}

void LightDetailController::onColorChanged(int r, int g, int b)
{
    app->hue->setColorRgb(mLight->id, r, g, b);
}

void LightDetailController::onSliderValueChanged(float value)
{
    app->hue->setBrightness(mLight->id, (int)(254 * value));
}