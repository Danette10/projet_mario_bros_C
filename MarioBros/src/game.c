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
    player->rect.x = 15;
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

void createEnemy(Enemy *enemy, SDL_Renderer *renderer, const char *imagePath) {
    // Charger l'image de l'ennemi
    SDL_Surface *enemyImage = SDL_LoadBMP(imagePath);

    // Redimensionner l'image de l'ennemi
    SDL_Surface *enemyResize = SDL_CreateRGBSurface(0, 16, 16, 32, 0, 0, 0, 0);

    SDL_BlitScaled(enemyImage, NULL, enemyResize, NULL);

    // Rendre le vert transparent
    SDL_SetColorKey(enemyResize, SDL_TRUE, SDL_MapRGB(enemyResize->format, 0, 255, 0));

    // Créer une texture à partir de l'image
    enemy->texture = SDL_CreateTextureFromSurface(renderer, enemyResize);
    if (enemy->texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }

    // Initialiser le rectangle de l'ennemi
    enemy->rect.x = 300;
    enemy->rect.y = 180;
    enemy->rect.w = enemyImage->w;
    enemy->rect.h = enemyImage->h;

    // Initialiser la vitesse de déplacement de l'ennemi
    enemy->x_velocity = 5;

    // Afficher l'ennemi à l'écran
    SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);
    SDL_RenderPresent(renderer);

    // Libérer la mémoire
    SDL_FreeSurface(enemyImage);
}

// je veux une fonction qui récupère seulement la position en x du joueur
int playerPositionX(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect playerRect) {

    int x = playerRect.x;

    return x;
}

void moveEnemy(Enemy *enemy, SDL_Renderer *renderer, Player *player) {

    SDL_RenderClear(renderer);

    if (enemy->rect.x >= 300 && enemy->rect.x <= 400) {
        enemy->rect.x += enemy->x_velocity;
    } else {
        enemy->x_velocity = -enemy->x_velocity;
        enemy->rect.x += enemy->x_velocity;
    }
    // Create background
    createBackground(renderer, "../include/ressources/images/background/desert/desert1.bmp", 0, 0 , WIDTH, HEIGHT);

    SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(100);

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

bool keys[SDL_NUM_SCANCODES];
bool isJumping = false;
bool isMovingRight = false;

void handlePlayerMovement(Player *player, SDL_Event event, SDL_Renderer *renderer, Enemy *enemy) {
    // check for key press events
    if (event.type == SDL_KEYDOWN) {

        if (event.key.keysym.sym == SDLK_RIGHT) {
            keys[SDL_SCANCODE_RIGHT] = true;
            if (player->rect.x < WIDTH - player->rect.w) {
                player->rect.x += 10;
            }
            isMovingRight = true;
        }
        if (event.key.keysym.sym == SDLK_LEFT) {
            keys[SDL_SCANCODE_LEFT] = true;
            if (player->rect.x > 15) {
                player->rect.x -= 10;
            }
        }
        if (event.key.keysym.sym == SDLK_SPACE) {
            keys[SDL_SCANCODE_SPACE] = true;
            if (player->rect.y == 165 && !isJumping) {
                player->rect.y -= 30;
            }
            isJumping = true;
        }

        // Si key.right est true et que key.space est true, alors le joueur saute et va à droite en même temps
        if (keys[SDL_SCANCODE_RIGHT] && keys[SDL_SCANCODE_SPACE] && isMovingRight) {
            if (player->rect.x < WIDTH - player->rect.w) {
                player->rect.x += 10;
            }
            if (player->rect.y == 165 && !isJumping) {
                player->rect.y -= 30;
            }
            isJumping = true;
        }
    }
        // check for key release events
    else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_RIGHT) {
            keys[SDL_SCANCODE_RIGHT] = false;
            isMovingRight = false;
        }
        if (event.key.keysym.sym == SDLK_LEFT) {
            keys[SDL_SCANCODE_LEFT] = false;
        }
        if (event.key.keysym.sym == SDLK_SPACE) {
            keys[SDL_SCANCODE_SPACE] = false;
        }
    }

    if (player->pv == 0) {
        SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
        playerIsDead(renderer, "../include/ressources/images/background/Gameover.bmp");
    }

    // clear the renderer
    SDL_RenderClear(renderer);

    // move the enemy
    moveEnemy(enemy, renderer, player);

    // render the player's texture
    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);

    // Si le joueur n'est pas sur le sol, il tombe
    if (player->rect.y < 165) {
        player->rect.y += 15;
    }

    // Si le joueur est sur le sol, il ne peut plus sauter
    if (player->rect.y >= 165) {
        isJumping = false;
    }
}


void loopGame(SDL_Renderer *renderer) {

    Player player;
    initPlayer(&player, renderer, "../include/ressources/images/sprite/mario/mario_normal_1.bmp", 100);

    Enemy enemy;
    createEnemy(&enemy, renderer, "../include/ressources/images/sprite/goomba/goomba_1.bmp");

    createBackground(renderer, "../include/ressources/images/background/desert/desert1.bmp", 0, 0, WIDTH, HEIGHT);


    SDL_Event event;

    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                // On libère la mémoire avant de quitter
                SDL_DestroyTexture(player.texture);
                exit(0);
                return;
            }

            handlePlayerMovement(&player, event, renderer, &enemy);
        }

        // Déplacement de l'ennemi
        moveEnemy(&enemy, renderer, &player);

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
