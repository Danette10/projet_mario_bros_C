#include <SDL_video.h>
#include "define.h"
#include "playerMove.h"

void createPlayer(SDL_Renderer *renderer)
{
// On charge l'image du joueur
    SDL_Surface *player = SDL_LoadBMP("../include/ressources/images/sprite/mario/mario_normal.bmp");

    // On rezise l'image du joueur
    SDL_Surface *playerResize = SDL_CreateRGBSurface(0, 50, 50, 32, 0, 0, 0, 0);
    SDL_BlitScaled(player, NULL, playerResize, NULL);

    // On rend le vert (couleur de la clé) transparent
    SDL_SetColorKey(playerResize, SDL_TRUE, SDL_MapRGB(playerResize->format, 0, 255, 0));



    // On crée une texture à partir de l'image
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, playerResize);
    if (texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }



    // On crée un rectangle pour positionner le joueur à l'écran
    SDL_Rect playerRect;
    playerRect.x = 0;
    playerRect.y = 150;
    playerRect.w = 50;
    playerRect.h = 50;

    // On affiche le joueur à l'écran
    SDL_RenderCopy(renderer, texture, NULL, &playerRect);
    SDL_RenderPresent(renderer);

    SDL_Event event;

    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                // On libère la mémoire avant de quitter
                SDL_DestroyTexture(texture);
                SDL_FreeSurface(player);
                return;
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    int type = 1;
                    SDL_Delay(150);
                    if (playerRect.x < WIDTH - playerRect.w) {
                        playerRect.x = playerMove(renderer, texture, playerRect, type);
                    }
                }
                if(event.key.keysym.sym == SDLK_LEFT) {
                    int type = 2;
                    SDL_Delay(150);
                    if (playerRect.x > 0) {
                        playerRect.x = playerMove(renderer, texture, playerRect, type);
                    }
                }
                if(event.key.keysym.sym == SDLK_SPACE) {

                    if (playerRect.y == 150) {
                        int type = 3;
                        SDL_Delay(150);

                        playerRect.y = playerMove(renderer, texture, playerRect, type);

                        SDL_Delay(500);

                    }

                    // Efface la texture du joueur
                    SDL_RenderClear(renderer);
                    createBackground(renderer);
                    playerRect.y = 150;
                    SDL_RenderCopy(renderer, texture, NULL, &playerRect);
                    SDL_RenderPresent(renderer);

                }
            }
        }
    }
}