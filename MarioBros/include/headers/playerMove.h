#include <SDL_video.h>
#include "define.h"

int playerMove(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect playerRect, int type) {
// On efface le joueur à l'écran
    SDL_RenderClear(renderer);

    switch (type) {

        case 1:

            // On déplace le joueur de 10 pixels vers la droite
            playerRect.x += 10;

            // On affiche à nouveau le joueur et le décor
            createBackground(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &playerRect);
            SDL_RenderPresent(renderer);

            break;

        case 2:

            playerRect.x -= 10;

            createBackground(renderer);
            // Flip the player
            SDL_RenderCopyEx(renderer, texture, NULL, &playerRect, 0, NULL, SDL_FLIP_HORIZONTAL);
            SDL_RenderPresent(renderer);

            break;

        default:

            break;

    }

    return playerRect.x;
}