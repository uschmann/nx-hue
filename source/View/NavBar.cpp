#include "View/NavBar.h"
#include "App.h"

#include "Controller/GroupController.h"
#include "Controller/LightController.h"

NavBar::NavBar(int x, int y)
: View(x, y, 500, 720 -90)
{
    int padding = 40;

    mGroupsButton = new NavBarButton(0, mY + padding, "Your Rooms");
    mLightsButton = new NavBarButton(0, mY + padding + mGroupsButton->getHeight(), "All Lights");
    mSettingsButton = new NavBarButton(0, mY + getHeight() - mGroupsButton->getHeight(), "Settings");
}

void NavBar::onDraw(SDL_Renderer* renderer)
{
    SDL_Rect bgRect = { mX, mY, mWidth, mHeight };
    SDL_SetRenderDrawColor(renderer, 20, 49, 100, 0xFF);
    SDL_RenderFillRect(renderer, &bgRect);

    mGroupsButton->onDraw(renderer);
    mLightsButton->onDraw(renderer);
    mSettingsButton->onDraw(renderer);
}

bool NavBar::onEvent(SDL_Event* event)
{
    if(event->type == SDL_USEREVENT) {
        TapEvent* e = (TapEvent*)event->user.data1;
        if(mGroupsButton->isTapped(e)) {
            App::getInstance()->startController(new GroupController());
        }

        if(mLightsButton->isTapped(e)) {
            App::getInstance()->startController(new LightController());
        }

        if(mSettingsButton->isTapped(e)) {
            printf("Settings\n");
        }
    }

    return false;
}