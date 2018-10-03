#include "Controller/LightController.h"

#include <stdio.h>

void LightController::onCreate(App * app)
{
    BaseController::onCreate(app);

    mNavBar->mGroupsButton->setActive(false);
    mNavBar->mSettingsButton->setActive(false);
    mNavBar->mLightsButton->setActive(true);

    mLights = app->hue->getLights();

    mLightItems = new vector<LightItem*>;
    for(int i = 0; i < mLights->size(); i++)
    {
        mLightItems->push_back(new LightItem(&mLights->at(i), mNavBar->getWidth() + 40, mActionBar->getHeight() + 40 + 140 * i));
    }
}

bool LightController::onEvent(SDL_Event * event)
{
    BaseController::onEvent(event);
    for(int i = 0; i < mLights->size(); i++)
    {
        mLightItems->at(i)->onEvent(event);
    }
    return false;
}

void LightController::onDraw(SDL_Renderer* renderer)
{
    BaseController::onDraw(renderer);

    for(int i = 0; i < mLights->size(); i++)
    {
        mLightItems->at(i)->onDraw(renderer);
    }
}