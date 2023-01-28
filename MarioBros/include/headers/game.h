#include <SDL_video.h>
#include <stdbool.h>
#include "define.h"

typedef SDL_Renderer Renderer;

// Structure for the player
typedef struct {
    char *name;
    char *imagePath;
    SDL_Texture *texture;
    SDL_Rect rect;
    int pv;
} Player;

// Structure for the enemy
typedef struct {
    char *name;
    char *imagePath;
    SDL_Texture *texture;
    SDL_Rect rect;
    int x_velocity;
} Enemy;

// Player functions
void initPlayer(Player *player, Renderer *renderer, char *name, char *imagePath);
void createBackground(SDL_Renderer *renderer, char *imagePath, int x, int y, int w, int h);
void handlePlayerMovement(Player *player, SDL_Event event, Renderer *renderer, Enemy *enemy);
void playerIsDead(SDL_Renderer *renderer, char *imagePath);

// Enemy functions
void createEnemy(Enemy *enemy, SDL_Renderer *renderer, char *name, char *imagePath);
void moveEnemy(Enemy *enemy, SDL_Renderer *renderer, Player *player);
void enemyDeath(Enemy *enemy, SDL_Renderer *renderer, Player *player);

// Game functions
void loopGame(SDL_Renderer *renderer);

// Utility functions
void playMusic(char *musicPath, int type);