#include "Controller/GroupDetailController.h"
#include "View/LightItem.h"
#include "Utils.h"

GroupDetailController::GroupDetailController(char* groupId)
{
    mGroupId = groupId;
}

void GroupDetailController::onCreate(App * app)
{
    BaseController::onCreate(app);

    mNavBar->mGroupsButton->setActive(true);
    mNavBar->mLightsButton->setActive(false);    
    mNavBar->mSettingsButton->setActive(false);

    mLightsScrollView = new ScrollView(
        mNavBar->getWidth() + 40, 
        mActionBar->getHeight() + 80 + 30, 
        1280 - mNavBar->getWidth() - 80,
        720 - mActionBar->getHeight() - 80 + 30
    );

    mGroup = app->hue->getGroupById(mGroupId);

    for(int i = 0; i < mGroup->lights->size(); i++) {
        mLightsScrollView->addChild(new LightItem(mGroup->lights->at(i), 0, 0));
    }
}

bool GroupDetailController::onEvent(SDL_Event * event)
{
    BaseController::onEvent(event);
    mLightsScrollView->onEvent(event);
    return false;
}

void GroupDetailController::onDraw(SDL_Renderer* renderer)
{
    BaseController::onDraw(renderer);

    TTF_Font* boldFont = app->assetManager->boldFont;
    TTF_Font* regularFont = app->assetManager->regularFont;

    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

    Util_DrawText(renderer, mGroup->name, boldFont, textColor, mNavBar->getWidth() + 40, mActionBar->getHeight() + 40);

    mLightsScrollView->onDraw(renderer);
}