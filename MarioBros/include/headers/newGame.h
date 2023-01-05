#include <SDL_video.h>
#include "define.h"
#include "createBackground.h"
#include "createPlayer.h"

void newGame(SDL_Renderer *renderer)
{
    createBackground(renderer);
    createPlayer(renderer);

    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                return;
            }

        }
    }
}