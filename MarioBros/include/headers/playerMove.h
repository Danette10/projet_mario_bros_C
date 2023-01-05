#include <SDL_video.h>
#include "define.h"

int playerMove(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect playerRect) {
// On efface le joueur à l'écran
    SDL_RenderClear(renderer);

    // On déplace le joueur de 10 pixels vers la droite
    playerRect.x += 10;

// On affiche à nouveau le joueur et le décor
    createBackground(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &playerRect);
    SDL_RenderPresent(renderer);

    return playerRect.x;
}