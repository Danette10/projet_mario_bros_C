#include <SDL.h>
#include "../include/headers/game.h"

void initPlayer(Player *player, SDL_Renderer *renderer, const char *imagePath, int pv)
{
    // Load player image
    SDL_Surface *playerImage = SDL_LoadBMP(imagePath);

    // Resize player image
    SDL_Surface *playerResize = SDL_CreateRGBSurface(0, 16, 32, 32, 0, 0, 0, 0);
    SDL_BlitScaled(playerImage, NULL, playerResize, NULL);

    // Set green color as transparent
    SDL_SetColorKey(playerResize, SDL_TRUE, SDL_MapRGB(playerResize->format, 0, 255, 0));

    // Create texture from image
    player->texture = SDL_CreateTextureFromSurface(renderer, playerResize);
    if (player->texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }

    // Initialize player rect
    player->rect.x = 0;
    player->rect.y = 165;
    player->rect.w = 16;
    player->rect.h = 32;

    // Initialize player's pv
    player->pv = pv;

    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
    SDL_RenderPresent(renderer);

    // Free memory
    SDL_FreeSurface(playerImage);
}



void createBackground(SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h)
{
    // On charge l'image du décor
    SDL_Surface *background = SDL_LoadBMP(imagePath);

    // On crée une texture à partir de l'image
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, background);
    if (texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }

    // On définit une zone de rendu spécifique dans la fenêtre de rendu
    SDL_RenderSetViewport(renderer, &(SDL_Rect){x, y, w, h});

    // On affiche le décor à l'écran
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // On libère la mémoire
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(background);
}

int playerMove(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect playerRect, int type) {

    // On efface le joueur à l'écran
    SDL_RenderClear(renderer);

    SDL_Rect camera = {0, 0, WIDTH, HEIGHT};

    switch (type) {

        case 1:

            // On déplace le joueur de 10 pixels vers la droite
            playerRect.x += 10;
            playerRect.y = 165;

            createBackground(renderer, "../include/ressources/images/background/desert/desert1.bmp", camera.x, camera.y, WIDTH, HEIGHT);

            SDL_RenderCopy(renderer, texture, NULL, &playerRect);
            SDL_RenderPresent(renderer);

            break;

        case 2:

            playerRect.x -= 10;
            playerRect.y = 165;

            createBackground(renderer, "../include/ressources/images/background/desert/desert1.bmp", camera.x, camera.y, WIDTH, HEIGHT);
            // Flip the player
            SDL_RenderCopyEx(renderer, texture, NULL, &playerRect, 0, NULL, SDL_FLIP_HORIZONTAL);
            SDL_RenderPresent(renderer);

            break;

        case 3:

            playerRect.y -= 30;
            // Garder sa position en x
            int x = playerRect.x;

            createBackground(renderer, "../include/ressources/images/background/desert/desert1.bmp", camera.x, camera.y, WIDTH, HEIGHT);
            SDL_RenderCopy(renderer, texture, NULL, &playerRect);
            SDL_RenderPresent(renderer);

            // On replace le joueur à sa position en x
            playerRect.x = x;

            break;

        default:

            break;

    }

    return playerRect.x;
}

int stateSpace = 0;

void handlePlayerMovement(Player *player, SDL_Event event, SDL_Renderer *renderer)
{
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RIGHT) {
            int type = 1;
            SDL_Delay(150);
            if (player->rect.x < WIDTH - player->rect.w) {
                player->rect.x = playerMove(renderer, player->texture, player->rect, type);
            }
        }
        if(event.key.keysym.sym == SDLK_LEFT) {
            int type = 2;
            SDL_Delay(150);
            if (player->rect.x > 0) {
                player->rect.x = playerMove(renderer, player->texture, player->rect, type);
            }
        }
        if(event.key.keysym.sym == SDLK_SPACE) {

            if (player->rect.y == 165 && stateSpace == 0) {
                int type = 3;
                SDL_Delay(150);
                player->rect.y = playerMove(renderer, player->texture, player->rect, type);
                SDL_Delay(400);

            }else{
                stateSpace = 1;
            }

            // Clear player texture
            SDL_RenderClear(renderer);
            createBackground(renderer, "../include/ressources/images/background/desert/desert1.bmp", 0, 0, WIDTH, HEIGHT);
            player->rect.y = 165;
            SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
            SDL_RenderPresent(renderer);

            SDL_Delay(150);
            stateSpace = 0;

        }

        if (player->pv == 0){
            SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
            playerIsDead(renderer, "../include/ressources/images/background/Gameover.bmp");
        }
    }
}

void createPlayer(SDL_Renderer *renderer, const char *imagePath) {
    Player player;
    initPlayer(&player, renderer, imagePath, 100);

    SDL_Event event;

    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                // On libère la mémoire avant de quitter
                SDL_DestroyTexture(player.texture);
                exit(0);
                return;
            }
            handlePlayerMovement(&player, event, renderer);
        }
    }
}

void playerIsDead(SDL_Renderer *renderer, const char *imagePath) {
    SDL_Surface *playerImage = SDL_LoadBMP(imagePath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, playerImage);
    if (texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }

    // On supprime background et player
    SDL_RenderClear(renderer);

    // On affiche le Gameover
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // On libère la mémoire
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(playerImage);


}
