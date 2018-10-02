#include "Utils.h"

void Util_DrawText(SDL_Renderer* renderer, const char* text , TTF_Font* font, SDL_Color color, int x, int y)
{
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect textRect = { x, y, surfaceMessage->w, surfaceMessage->h };
    
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(texture);
}