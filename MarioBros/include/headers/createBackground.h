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

// On affiche la texture dans la fenêtre
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

// On libère la mémoire
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(background);
}