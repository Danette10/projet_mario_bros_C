#include <SDL_video.h>
#include "define.h"

typedef struct Player Player;
typedef SDL_Renderer Renderer;

struct Player {
    SDL_Texture *texture;
    SDL_Rect rect;
    int pv;
};

void initPlayer(Player *player, Renderer *renderer, const char *imagePath, int pv);

void createBackground(SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h);

void handlePlayerMovement(Player *player, SDL_Event event, Renderer *renderer);

void createPlayer(SDL_Renderer *renderer, const char *imagePath);

int playerMove(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect playerRect, int type);

void playerIsDead(SDL_Renderer *renderer, const char *imagePath);