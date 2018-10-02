#pragma once

class AssetManager {
    public:
        TTF_Font* regularFont;
        TTF_Font* boldFont;

        SDL_Texture* toggleButton;

        bool load(SDL_Renderer* renderer);
};
