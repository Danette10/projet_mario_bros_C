#include <SDL.h>
#include <SDL_audio.h>
#include "../include/headers/game.h"
#include "../include/headers/utilities.h"

// Function to check collision
bool checkCollision(SDL_Rect a, SDL_Rect b) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if (bottomA <= topB) {
        return false;
    }

    if (topA >= bottomB) {
        return false;
    }

    if (rightA <= leftB) {
        return false;
    }

    if (leftA >= rightB) {
        return false;
    }

    return true;
}

// Function to create background
void createBackground(SDL_Renderer *renderer, Background *background)
{
    // Load background image
    SDL_Surface *backgroundImage = SDL_LoadBMP(background->imagePath);

    background->rect.w = backgroundImage->w;
    background->rect.h = backgroundImage->h;
    background->rect.y = -484;

    // Create texture from image
    background->texture = SDL_CreateTextureFromSurface(renderer, backgroundImage);
    if (background->texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }


    SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

    // Free memory
    SDL_FreeSurface(backgroundImage);
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
    player->rect.x = 150;
    player->rect.y = 125;
    player->rect.w = 16;
    player->rect.h = 32;

    // Initialize player's pv
    player->pv = 100;

    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);
    SDL_RenderPresent(renderer);

    // Free memory
    SDL_FreeSurface(playerImage);
}


bool isJumping = false;
bool isMovingRight = false;
bool isMovingLeft = false;

// Function to handle player movement
void handlePlayerMovement(Player *player, SDL_Event event, SDL_Renderer *renderer, Enemy *enemy, Object *object, Background *background) {

    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RIGHT] && state[SDL_SCANCODE_UP]) {

        isMovingLeft = false;
        isMovingRight = true;

        isJumping = true;

        int frameCounter = 0;

        while (frameCounter < 30) {

            SDL_RenderClear(renderer);

            background->rect.y += 2;


            background->rect.x -= 2;

            object->rect.x -= 2;

            enemy->rect.x -= 2;

            enemy->rect.y += 2;

            object->rect.y += 2;

            SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

            SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

            SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

            SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);

            SDL_RenderPresent(renderer);

            SDL_Delay(10);

            frameCounter++;

        }

        while (frameCounter < 60) {

            SDL_RenderClear(renderer);

            background->rect.y -= 2;


            background->rect.x -= 2;

            object->rect.x -= 2;

            enemy->rect.x -= 2;

            enemy->rect.y -= 2;

            object->rect.y -= 2;

            SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

            SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

            SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

            SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);

            SDL_RenderPresent(renderer);

            SDL_Delay(10);

            frameCounter++;

        }

        SDL_PumpEvents();
        SDL_FlushEvent(SDL_KEYUP);

    }else if(state[SDL_SCANCODE_LEFT] && state[SDL_SCANCODE_UP]) {

        isMovingLeft = true;
        isMovingRight = false;

        isJumping = true;

        int frameCounter = 0;

        while (frameCounter < 30) {

            SDL_RenderClear(renderer);

            background->rect.y += 2;

            // Si le background est toujours dans la fenêtre on bouge le background sinon on bouge le joueur
            if (background->rect.x < 0) {

                background->rect.x += 2;

                object->rect.x += 2;

                enemy->rect.x += 2;

            } else {

                player->rect.x -= 2;

            }

            enemy->rect.y += 2;

            object->rect.y += 2;

            SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

            SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

            SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

            SDL_RenderCopyEx(renderer, player->texture, NULL, &player->rect, 0, NULL, SDL_FLIP_HORIZONTAL);

            SDL_RenderPresent(renderer);

            SDL_Delay(10);

            frameCounter++;

        }

        while (frameCounter < 60) {

            SDL_RenderClear(renderer);

            background->rect.y -= 2;

            // Si le background est toujours dans la fenêtre on bouge le background sinon on bouge le joueur
            if (background->rect.x < 0) {

                background->rect.x += 2;

                object->rect.x += 2;

                enemy->rect.x += 2;

            } else {

                player->rect.x -= 2;

            }

            enemy->rect.y -= 2;

            object->rect.y -= 2;

            SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

            SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

            SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

            SDL_RenderCopyEx(renderer, player->texture, NULL, &player->rect, 0, NULL, SDL_FLIP_HORIZONTAL);

            SDL_RenderPresent(renderer);

            SDL_Delay(10);

            frameCounter++;

        }

        SDL_PumpEvents();
        SDL_FlushEvent(SDL_KEYDOWN);
        SDL_FlushEvent(SDL_KEYUP);

    }else if (event.type == SDL_KEYUP) {

        if (event.key.keysym.sym == SDLK_RIGHT) {

            background->rect.x -= 10;

            object->rect.x -= 10;

            isMovingRight = true;
            isMovingLeft = false;
            isJumping = false;

        }

        if (event.key.keysym.sym == SDLK_LEFT) {

            if (background->rect.x < 0) {

                background->rect.x += 10;

                object->rect.x += 10;

            }else if(player->rect.x > 100) {

                player->rect.x -= 10;

            }

            isMovingLeft = true;
            isMovingRight = false;
            isJumping = false;

        }

        if (event.key.keysym.sym == SDLK_UP) {

            isJumping = true;

            int frameCounter = 0;

            while (frameCounter < 30) {

                SDL_RenderClear(renderer);

                background->rect.y += 2;

                enemy->rect.y += 2;

                object->rect.y += 2;

                SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

                SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

                SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

                if(isMovingLeft){

                    SDL_RenderCopyEx(renderer, player->texture, NULL, &player->rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }else{

                    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);

                }

                SDL_RenderPresent(renderer);

                SDL_Delay(10);

                frameCounter++;

            }

            while (frameCounter < 60) {

                SDL_RenderClear(renderer);

                background->rect.y -= 2;

                enemy->rect.y -= 2;

                object->rect.y -= 2;

                SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

                SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

                SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

                if(isMovingLeft){

                    SDL_RenderCopyEx(renderer, player->texture, NULL, &player->rect, 0, NULL, SDL_FLIP_HORIZONTAL);

                }else{

                    SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);

                }

                SDL_RenderPresent(renderer);

                SDL_Delay(10);

                frameCounter++;

            }

        } else if(background->rect.x >= -350 && background->rect.x <= -330) {

            SDL_PumpEvents();
            SDL_FlushEvent(SDL_KEYDOWN);
            SDL_FlushEvent(SDL_KEYUP);

            int frameCounter = 0;

            while (player->rect.y < HEIGHT) {

                SDL_RenderClear(renderer);

                player->rect.y += 2;

                SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

                SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

                SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

                // Mettre la tete du joueur à l'envers
                SDL_RenderCopyEx(renderer, player->texture, NULL, &player->rect, 180, NULL, SDL_FLIP_HORIZONTAL);

                SDL_RenderPresent(renderer);

                SDL_Delay(10);

                frameCounter++;

            }

            return playerIsDead(renderer, "../include/ressources/images/background/Gameover.bmp");

        }

    }

    if (isJumping && checkCollision(player->rect, enemy->rect)) {
        enemyDeath(enemy, renderer, player, object, background);

        enemy->rect.x = 0;
        enemy->rect.y = 0;
        enemy->rect.w = 0;
        enemy->rect.h = 0;

        SDL_DestroyTexture(enemy->texture);

    }else{

        if (!isJumping && checkCollision(player->rect, enemy->rect)) {

            if(player->pv > 0){

                if(player->pv == 150){

                    player->rect.w -= 10;
                    player->rect.h -= 10;
                    player->rect.y += 5;
                    
                }
                player->pv -= 10;

            }else{

                player->pv = 0;
                return;

            }

        }

    }

    if (!isJumping && checkCollision(player->rect, object->rect)) {

        player->pv += 50;

        player->rect.w += 10;
        player->rect.h += 10;
        player->rect.y -= 5;

        object->rect.x = 0;
        object->rect.y = 0;
        object->rect.w = 0;
        object->rect.h = 0;

        SDL_DestroyTexture(object->texture);
    }

    /**
     * Problème pour la victoire
     */

/*    if(background->rect.x == -1800){

        SDL_PumpEvents();
        SDL_FlushEvent(SDL_KEYDOWN);
        SDL_FlushEvent(SDL_KEYUP);

        int victories = readTextFile("../include/ressources/scores/victories.txt");
        victories++;
        writeTextFile(victories, "../include/ressources/scores/victories.txt");

        return playerIsDead(renderer, "../include/ressources/images/background/YouWin.bmp");

    }*/

    // clear the renderer
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

    SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

    SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

    // move the enemy
    moveEnemy(enemy, renderer, player, object, background);

    isJumping = false;

}

// Function to check if the player is dead
void playerIsDead(SDL_Renderer *renderer, char *imagePath) {
    SDL_Surface *playerImage = SDL_LoadBMP(imagePath);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, playerImage);
    if (texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }

    // Augmenter le nombre de morts$
    int deaths = readTextFile("../include/ressources/scores/deaths.txt");
    deaths++;
    writeTextFile(deaths, "../include/ressources/scores/deaths.txt");

    // Supprimer tout ce qui est affiché
    SDL_RenderClear(renderer);

    // Afficher l'image de Game Over
    SDL_RenderCopy(renderer, texture, NULL, NULL);

    // Mettre à jour l'affichage
    SDL_RenderPresent(renderer);

    SDL_CloseAudioDevice(2);

    playMusic("../include/ressources/sounds/music/gameover.wav", 1);

    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                SDL_Quit();
                exit(0);
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
    enemy->rect.x = 800;
    enemy->rect.y = 145;
    enemy->rect.w = enemyImage->w;
    enemy->rect.h = enemyImage->h;

    // Initialiser la vitesse de déplacement de l'ennemi
    enemy->x_velocity = 5;

    // Afficher l'ennemi à l'écran
    SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);
    SDL_RenderPresent(renderer);

    // Libérer la mémoire9/
    SDL_FreeSurface(enemyImage);
}

// Function to move the enemy
bool moveRight = true;
void moveEnemy(Enemy *enemy, SDL_Renderer *renderer, Player *player, Object *object, Background *background) {
    SDL_RenderClear(renderer);

    if (moveRight) {
        if (enemy->rect.x < 900 + background->rect.x) {
            enemy->rect.x += enemy->x_velocity;
        } else {
            moveRight = false;
        }
    } else {
        if (enemy->rect.x > 800 + background->rect.x) {
            enemy->rect.x -= enemy->x_velocity;
        } else {
            moveRight = true;
        }
    }

    SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

    SDL_RenderCopy(renderer, enemy->texture, NULL, &enemy->rect);

    if(isMovingLeft){

        SDL_RenderCopyEx(renderer, player->texture, NULL, &player->rect, 0, NULL, SDL_FLIP_HORIZONTAL);

    }else{

        SDL_RenderCopy(renderer, player->texture, NULL, &player->rect);

    }

    // Afficher l'objet en prenant en compte le décalage du fond
    SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

    SDL_RenderPresent(renderer);

    SDL_Delay(100);

    if (!isJumping && checkCollision(enemy->rect, player->rect)) {

        if(player->pv > 0){

            if(player->pv == 150){

                player->rect.w -= 10;
                player->rect.h -= 10;
                player->rect.y += 10;

            }
            player->pv -= 10;



        }else{

            player->pv = 0;
            // Supprimer le joueur
            SDL_DestroyTexture(player->texture);

            // Supprimer l'ennemi
            SDL_DestroyTexture(enemy->texture);

            return playerIsDead(renderer, "../include/ressources/images/background/Gameover.bmp");

        }
    }

}

// Function to check if the enemy is dead
void enemyDeath(Enemy *enemy, SDL_Renderer *renderer, Player *player, Object *object, Background *background) {
    SDL_RenderClear(renderer);

    // Afficher le fond
    SDL_RenderCopy(renderer, background->texture, NULL, &background->rect);

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

    SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);

    SDL_RenderPresent(renderer);

    SDL_Delay(200);

}

// Function to create a new object
void createObject(Object *object, SDL_Renderer *renderer, int x, int y, char *name, char *imagePath) {

    // Initialiser le nom de l'objet
    object->name = name;

    object->imagePath = imagePath;
    // Charger l'image de l'objet
    SDL_Surface *objectImage = SDL_LoadBMP(object->imagePath);

    // Redimensionner l'image de l'objet
    SDL_Surface *objectResize = SDL_CreateRGBSurface(0, 16, 16, 32, 0, 0, 0, 0);

    SDL_BlitScaled(objectImage, NULL, objectResize, NULL);

    // Rendre le vert transparent
    SDL_SetColorKey(objectResize, SDL_TRUE, SDL_MapRGB(objectResize->format, 0, 255, 0));

    // Créer une texture à partir de l'image
    object->texture = SDL_CreateTextureFromSurface(renderer, objectResize);
    if (object->texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }

    // Initialiser le rectangle de l'objet
    object->rect.x = x;
    object->rect.y = y;
    object->rect.w = objectImage->w;
    object->rect.h = objectImage->h;

    // Initialiser la vitesse de déplacement de l'objet
    object->x_velocity = 5;

    // Afficher l'objet à l'écran
    SDL_RenderCopy(renderer, object->texture, NULL, &object->rect);
    SDL_RenderPresent(renderer);

    // Libérer la mémoire
    SDL_FreeSurface(objectImage);
}


// Game loop
void loopGame(SDL_Renderer *renderer) {

    Player player;
    initPlayer(&player, renderer, "Mario", "../include/ressources/images/sprite/mario/mario_normal_1.bmp");

    Enemy enemy;
    createEnemy(&enemy, renderer, "Goomba", "../include/ressources/images/sprite/goomba/goomba_1.bmp");

    Object object;
    createObject(&object, renderer, 700, 145,"PowerUp", "../include/ressources/images/sprite/items/power_up.bmp");

    Background background;
    background.imagePath = "../include/ressources/images/background/desert/desert1.bmp";
    background.rect.x = 0;
    createBackground(renderer, &background);

    SDL_Event event;

    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                // On libère la mémoire avant de quitter
                SDL_DestroyTexture(player.texture);
                exit(0);
            }

            // Si le joueur n'a plus de vie, on ouvre la fonction de game over
            if(player.pv == 0){

                // Supprimer le joueur
                SDL_DestroyTexture(player.texture);

                // Supprimer l'ennemi
                SDL_DestroyTexture(enemy.texture);

                playerIsDead(renderer, "../include/ressources/images/background/Gameover.bmp");
            }else{
                handlePlayerMovement(&player, event, renderer, &enemy, &object, &background);
            }
        }

        // Déplacement de l'ennemi
        moveEnemy(&enemy, renderer, &player, &object, &background);

    }
}
