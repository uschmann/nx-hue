#pragma once

class AssetManager {
    public:
        TTF_Font* regularFont;
        TTF_Font* boldFont;

        bool load();
};
