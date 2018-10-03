#include "Controller/LightController.h"

#include <stdio.h>

void LightController::onCreate(App * app)
{
    BaseController::onCreate(app);

    mNavBar->mGroupsButton->setActive(false);
    mNavBar->mSettingsButton->setActive(false);
    mNavBar->mLightsButton->setActive(true);

    mLights = app->hue->getLights();

    mScrollView = new ScrollView(
        mNavBar->getWidth() + 40, 
        mActionBar->getHeight() + 40, 
        1280 - mNavBar->getWidth() - 80,
        720 - mActionBar->getHeight() - 40
    );
    for(int i = 0; i < mLights->size(); i++)
    {
        mScrollView->addChild(new LightItem(&mLights->at(i), 0, 0));
    }
}

bool LightController::onEvent(SDL_Event * event)
{
    BaseController::onEvent(event);
    mScrollView->onEvent(event);
    return false;
}

void LightController::onDraw(SDL_Renderer* renderer)
{
    BaseController::onDraw(renderer);
    mScrollView->onDraw(renderer);
}