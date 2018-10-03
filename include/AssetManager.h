#pragma once

class AssetManager {
    public:
        TTF_Font* regularFont;
        TTF_Font* boldFont;

        SDL_Texture* toggleButton;
        SDL_Texture* pallette;
        SDL_Texture* list;
        SDL_Texture* shadow;

        SDL_Texture* colorWheel;
        SDL_Surface* colorWheelSurface;

        bool load(SDL_Renderer* renderer);
};
