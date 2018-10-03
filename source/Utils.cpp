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

double distance(double x1, double y1, double x2, double y2)
{
    double square_difference_x = (x2 - x1) * (x2 - x1);
    double square_difference_y = (y2 - y1) * (y2 - y1);
    double sum = square_difference_x + square_difference_y;
    double value = sqrt(sum);
    return value;
}