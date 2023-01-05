#include <SDL_video.h>
#include "define.h"

void createBackground(SDL_Renderer *renderer)
{
// On charge l'image du décor
    SDL_Surface *background = SDL_LoadBMP("../include/ressources/images/background/desert/desert1.bmp");

    // On crée une texture à partir de l'image
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background);
    if (texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }

    // On crée un rectangle pour positionner le décor à l'écran
    SDL_Rect backgroundRect;
    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.w = WIDTH;
    backgroundRect.h = HEIGHT;

    // On affiche le décor à l'écran
    SDL_RenderCopy(renderer, texture, NULL, &backgroundRect);
    SDL_RenderPresent(renderer);

    // On libère la mémoire
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(background);
}