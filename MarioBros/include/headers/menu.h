#include <SDL_video.h>
#include "define.h"

void displayMenu(char *menuArray[], int menuIndex, SDL_Window *window)
{
    // On charge l'image suivante
    SDL_Surface *menu = SDL_LoadBMP(menuArray[menuIndex]);

    SDL_Surface *menuSizeWindow = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
    SDL_BlitScaled(menu, NULL, menuSizeWindow, NULL);
    // Affichage de l'image
    SDL_BlitSurface(menuSizeWindow, NULL, SDL_GetWindowSurface(window), NULL);
    SDL_UpdateWindowSurface(window);
}