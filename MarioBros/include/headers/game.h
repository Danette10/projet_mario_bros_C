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
    int deplacementX;
} Enemy;

// Structure for the objects
typedef struct {
    char *name;
    char *imagePath;
    SDL_Texture *texture;
    SDL_Rect rect;
    int x_velocity;
} Object;

// Structure for the background
typedef struct {
    char *name;
    char *imagePath;
    SDL_Texture *texture;
    SDL_Rect rect;
    int x;
    int y;
    int w;
    int h;
} Background;

// Player functions
void initPlayer(Player *player, Renderer *renderer, char *name, char *imagePath);
void createBackground(Renderer *renderer, Background *background);
void handlePlayerMovement(Player *player, SDL_Event event, Renderer *renderer, Enemy *enemy, Object *object, Background *background);
void playerIsDead(Renderer *renderer, char *imagePath);

// Enemy functions
void createEnemy(Enemy *enemy, Renderer *renderer, char *name, char *imagePath);
void moveEnemy(Enemy *enemy, Renderer *renderer, Player *player, Object *object, Background *background);
void enemyDeath(Enemy *enemy, Renderer *renderer, Player *player, Object *object, Background *background);

// Object functions
void createObject(Object *object, Renderer *renderer, int x, int y, char *name, char *imagePath);

// Game functions
void loopGame(Renderer *renderer);
bool checkCollision(SDL_Rect a, SDL_Rect b);