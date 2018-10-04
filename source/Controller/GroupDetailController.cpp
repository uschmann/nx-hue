#include "Controller/GroupDetailController.h"
#include "View/LightItem.h"
#include "Utils.h"

const int STATE_LIST = 0;
const int STATE_SETTINGS = 1;

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
        mActionBar->getHeight() + 80 + 70, 
        1280 - mNavBar->getWidth() - 80,
        720 - mActionBar->getHeight() - 80 + 30
    );

    mGroup = app->hue->getGroupById(mGroupId);

    for(int i = 0; i < mGroup->lights->size(); i++) {
        mLightsScrollView->addChild(new LightItem(mGroup->lights->at(i), 0, 0));
    }

    mSettingsButton = new IconButton(app->assetManager->pallette, 1280 - 90 - 40, mActionBar->getHeight() + 20);
    mLightButton = new IconButton(app->assetManager->list, 1280 - 180 - 60, mActionBar->getHeight() + 20);
    mSettingsButton->setActive(true);
    mLightButton->setActive(false);
    mState = STATE_SETTINGS;

    mColorWheel = new ColorWheel(mNavBar->getWidth() + 40 + 350 - 210, mActionBar->getHeight() + 110);
    mColorWheel->setColorListener(this);

    mSlider = new Slider(mNavBar->getWidth() + 80, 720 - 80 , 1280 - (mNavBar->getWidth() + 160));
    mSlider->setSliderChangeListener(this);
    mSlider->setValue(0.5f);
}

bool GroupDetailController::onEvent(SDL_Event * event)
{
    BaseController::onEvent(event);

    if(event->type == SDL_USEREVENT) {
        TapEvent* e = (TapEvent*)event->user.data1;
        if(mLightButton->isTapped(e)) {
            mState = STATE_LIST;
            mLightButton->setActive(true);
            mSettingsButton->setActive(false);
            return true;
        }
        else if(mSettingsButton->isTapped(e)) {
            mState = STATE_SETTINGS;
            mLightButton->setActive(false);
            mSettingsButton->setActive(true);
            return true;
        }
    }

    if(mState == STATE_LIST) {
        mLightsScrollView->onEvent(event);
    }
    else {
        mSlider->onEvent(event);
        mColorWheel->onEvent(event);
    }
    
    return false;
}

void GroupDetailController::onDraw(SDL_Renderer* renderer)
{
    BaseController::onDraw(renderer);

    TTF_Font* boldFont = app->assetManager->boldFont;
    TTF_Font* regularFont = app->assetManager->regularFont;
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    Util_DrawText(renderer, mGroup->name, boldFont, textColor, mNavBar->getWidth() + 40, mActionBar->getHeight() + 40);

    mLightButton->onDraw(renderer);
    mSettingsButton->onDraw(renderer);

    if(mState == STATE_LIST) {
        mLightsScrollView->onDraw(renderer);
    }
    else {
        mSlider->onDraw(renderer);
        mColorWheel->onDraw(renderer);
    }
    
}

void GroupDetailController::onColorChanged(int r, int g, int b)
{
    app->hue->setGroupColorRgb(mGroup->id, r, g, b);
}

void GroupDetailController::onSliderValueChanged(float value)
{
    app->hue->setGroupBrightness(mGroup->id, ((float)254 * value));
}