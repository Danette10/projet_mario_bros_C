#include <SDL.h>
#include <SDL_audio.h>
#include "../include/headers/game.h"

// Function to play music
void playMusic(char *musicPath, int type) {

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_LoadWAV(musicPath, &wavSpec, &wavBuffer, &wavLength);

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        printf("Failed to open audio: %s \n", SDL_GetError());
        return;
    }

    // Jouer la musique
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    if(type == 1){
        while (SDL_GetQueuedAudioSize(deviceId) > 0) {
            SDL_Delay(100);
        }
    }

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

    // Create player
    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
    SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);
    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
    SDL_SetRenderTarget(renderer, NULL);

    // Code mamadou
    //Création d'un carré noir à 200 pixel de la gauche et 200 pixel du haut
    SDL_Rect madmadroom = {200, 100, 100, 100};
    //Création d'une texture noir
    SDL_Texture *madmadtexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 100, 100);

    //On dessine le carré noir dans la texture

    SDL_SetRenderTarget(renderer, madmadtexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &madmadroom);
    SDL_SetRenderTarget(renderer, NULL);

    // Si position du joueur est supérieur à 200, le joueur ne peut pas aller plus loin
    if (player->rect.x >= 200) {
        player->rect.x = 180;
    }

    // Afficher le carré noir à l'écran
    SDL_RenderCopy(renderer, madmadtexture, NULL, &madmadroom);

    // Code mamadou

    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(100);

}



void createBackground(SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h)
// Function to create background
void createBackground(SDL_Renderer *renderer, char *imagePath, int x, int y, int w, int h)
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

// Function to initialize player
void initPlayer(Player *player, SDL_Renderer *renderer, char *name, char *imagePath)
{
    // Load player image
    player->imagePath = imagePath;
    SDL_Surface *playerImage = SDL_LoadBMP(player->imagePath);

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

    player->name = name;

    // Initialize player rect
    player->rect.x = 15;
    player->rect.y = 165;
    player->rect.w = 16;
    player->rect.h = 32;

    // Initialize player's pv
    player->pv = 100;

    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
    SDL_RenderPresent(renderer);

    // Free memory
    SDL_FreeSurface(playerImage);
}


bool keys[SDL_NUM_SCANCODES];
bool isJumping = false;
bool isMovingRight = false;

// Function to handle player movement
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

    if (isJumping && player->rect.y < enemy->rect.y + enemy->rect.h && player->rect.y + player->rect.h > enemy->rect.y && player->rect.x < enemy->rect.x + enemy->rect.w && player->rect.x + player->rect.w > enemy->rect.x) {
        enemyDeath(enemy, renderer, player);

        enemy->rect.x = 0;
        enemy->rect.y = 0;
        enemy->rect.w = 0;
        enemy->rect.h = 0;

        SDL_DestroyTexture(enemy->texture);
    }else{

        if (player->rect.y == 165 && player->rect.y < enemy->rect.y + enemy->rect.h && player->rect.y + player->rect.h > enemy->rect.y && player->rect.x < enemy->rect.x + enemy->rect.w && player->rect.x + player->rect.w > enemy->rect.x) {
            if(player->pv > 0){
                player->pv -= 50;
            }else{
                player->pv = 0;
                return;
            }
        }
    }

    // clear the renderer
    SDL_RenderClear(renderer);

    // move the enemy
    moveEnemy(enemy, renderer, player);

    // render the player's texture
    SDL_Delay(10);
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

// Function to check if the player is dead
void playerIsDead(SDL_Renderer *renderer, char *imagePath) {
    SDL_Surface *playerImage = SDL_LoadBMP(imagePath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, playerImage);
    if (texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }

    // Supprimer tout ce qui est affiché
    SDL_RenderClear(renderer);

    // Afficher l'image de Game Over
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Mettre à jour l'affichage
    SDL_RenderPresent(renderer);

    SDL_CloseAudioDevice(2);

    playMusic("../include/ressources/sounds/music/gameover.wav", 1);


    // on reste dans cette boucle tant que l'utilisateur n'a pas appuyé sur echap
    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                exit(0);
                return;
            }
        }
    }

}

// Function to create an enemy
void createEnemy(Enemy *enemy, SDL_Renderer *renderer, char *name, char *imagePath) {

    // Initialiser le nom de l'ennemi
    enemy->name = name;

    enemy->imagePath = imagePath;
    // Charger l'image de l'ennemi
    SDL_Surface *enemyImage = SDL_LoadBMP(enemy->imagePath);

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

// Function to move the enemy
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

// Function to check if the enemy is dead
void enemyDeath(Enemy *enemy, SDL_Renderer *renderer, Player *player) {
    SDL_RenderClear(renderer);

    // Create background
    createBackground(renderer, "../include/ressources/images/background/desert/desert1.bmp", 0, 0 , WIDTH, HEIGHT);

    // Remplacer l'ennemi par un cadavre
    SDL_Surface *enemyImage = SDL_LoadBMP("../include/ressources/images/sprite/goomba/goomba_dead.bmp");
    SDL_Surface *enemyResize = SDL_CreateRGBSurface(0, 16, 16, 32, 0, 0, 0, 0);
    SDL_BlitScaled(enemyImage, NULL, enemyResize, NULL);
    SDL_SetColorKey(enemyResize, SDL_TRUE, SDL_MapRGB(enemyResize->format, 0, 255, 0));
    enemy->texture = SDL_CreateTextureFromSurface(renderer, enemyResize);
    if (enemy->texture == NULL) {
        printf("Could not create texture: %s \n", SDL_GetError());
        return;
    }

    SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
}


// Game loop
void loopGame(SDL_Renderer *renderer) {

    Player player;
    initPlayer(&player, renderer, "Mario", "../include/ressources/images/sprite/mario/mario_normal_1.bmp");

    Enemy enemy;
    createEnemy(&enemy, renderer, "Goomba", "../include/ressources/images/sprite/goomba/goomba_1.bmp");

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

            // Si le joueur n'a plus de vie, on ouvre la fonction de game over
            if(player.pv == 0){

                // Supprimer le joueur
                SDL_DestroyTexture(player.texture);

                // Supprimer l'ennemi
                SDL_DestroyTexture(enemy.texture);

                playerIsDead(renderer, "../include/ressources/images/background/Gameover.bmp");
            }else{
                handlePlayerMovement(&player, event, renderer, &enemy);
            }
        }

        // Déplacement de l'ennemi
        moveEnemy(&enemy, renderer, &player);

    }
}

