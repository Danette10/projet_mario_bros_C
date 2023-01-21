#include <SDL_video.h>
#include <stdbool.h>
#include "define.h"

typedef struct Player Player;
typedef SDL_Renderer Renderer;

struct Player {
    SDL_Texture *texture;
    SDL_Rect rect;
    int pv;
};

// Structure pour stocker les informations de l'ennemi
typedef struct {
    SDL_Texture *texture;
    SDL_Rect rect;
    int x_velocity;
} Enemy;

void initPlayer(Player *player, Renderer *renderer, const char *imagePath, int pv);

void createBackground(SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h);

void handlePlayerMovement(Player *player, SDL_Event event, Renderer *renderer, Enemy *enemy);

void loopGame(SDL_Renderer *renderer);

void playerIsDead(SDL_Renderer *renderer, const char *imagePath);

void createEnemy(Enemy *enemy, SDL_Renderer *renderer, const char *imagePath);

void moveEnemy(Enemy *enemy, SDL_Renderer *renderer, Player *player);

void enemyDeath(Enemy *enemy, SDL_Renderer *renderer, Player *player);