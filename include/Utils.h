#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void Util_DrawText(SDL_Renderer* renderer, const char* text , TTF_Font* font, SDL_Color color, int x, int y);
double distance(double x1, double y1, double x2, double y2);