#include <stdio.h>
#include <stdlib.h>
#include <SDL_audio.h>
#include <SDL_video.h>
#include <SDL.h>

const int WIDTH = 800, HEIGHT = 600;

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Mario Bros", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    if(window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // mettre une image de fond
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Surface *image = SDL_LoadBMP("../include/images/background/desert/desert1.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while(1) {
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                break;
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}