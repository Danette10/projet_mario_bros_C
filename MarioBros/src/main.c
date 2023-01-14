#include <stdio.h>
#include <stdlib.h>
#include <SDL_audio.h>
#include <SDL_video.h>
#include <SDL.h>
#include "../include/headers/menu.h"

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Could not create renderer: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *icon = SDL_LoadBMP("../include/ressources/images/icon/mario_logo.bmp");
    SDL_SetWindowIcon(window, icon);

    SDL_ShowCursor(SDL_DISABLE);

    if(window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_LoadWAV("../include/ressources/sounds/music/mario_theme.wav", &wavSpec, &wavBuffer, &wavLength);
    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    SDL_PauseAudioDevice(deviceId, 0);

    Menu menu;

    initMenu(&menu, 4);

    addOption(&menu, "../include/ressources/images/menu/menu_new_game_selected.bmp", 0);
    addOption(&menu, "../include/ressources/images/menu/menu_load_game_selected.bmp", 1);
    addOption(&menu, "../include/ressources/images/menu/menu_shop_selected.bmp", 2);
    addOption(&menu, "../include/ressources/images/menu/menu_quit_selected.bmp", 3);

    displayMenu(&menu, renderer);

    while (1) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {

                SDL_CloseAudioDevice(deviceId);
                SDL_FreeWAV(wavBuffer);
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;

            }

            handleMenuNavigation(&menu, renderer, &event);

        }

        if (SDL_GetQueuedAudioSize(deviceId) == 0) {

            SDL_QueueAudio(deviceId, wavBuffer, wavLength);

        }
    }
}