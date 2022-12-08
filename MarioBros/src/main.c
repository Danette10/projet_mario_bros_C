#include <stdio.h>
#include <stdlib.h>
#include <SDL_audio.h>
#include <SDL_video.h>
#include <SDL.h>

const int WIDTH = 900, HEIGHT = 550;

int main(int argc, char *argv[]) {
    SDL_Window *window;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Mario Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Surface *icon = SDL_LoadBMP("../include/ressources/images/icon/mario_logo.bmp");
    SDL_SetWindowIcon(window, icon);

    SDL_Surface *cursor = SDL_LoadBMP("../include/ressources/images/icon/Mario_s-Normal.bmp");
    SDL_SetColorKey(cursor, SDL_TRUE, SDL_MapRGB(cursor->format, 255, 255, 255));
    SDL_Cursor *cursor2 = SDL_CreateColorCursor(cursor, 0, 0);
    SDL_SetCursor(cursor2);

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

    char *menuArray[4] = {"../include/ressources/images/menu/menu_new_game_selected.bmp",
                          "../include/ressources/images/menu/menu_load_game_selected.bmp",
                            "../include/ressources/images/menu/menu_shop_selected.bmp",
                            "../include/ressources/images/menu/menu_quit_selected.bmp"};
    int count = 0;

    while (1) {

        SDL_Event event;

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {

                SDL_CloseAudioDevice(deviceId);
                SDL_FreeWAV(wavBuffer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;

            }
            if (event.type == SDL_KEYDOWN) {
                // Compte le nombre de fois que l'on appuie sur une touche

                if(count > 4) {
                    count = 0;
                }else{
                    count++;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {

                    // On charge l'image suivante
                    SDL_Surface *menu = SDL_LoadBMP(menuArray[count]);

                    SDL_Surface *menuSizeWindow = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
                    SDL_BlitScaled(menu, NULL, menuSizeWindow, NULL);
                    // Affichage de l'image
                    SDL_BlitSurface(menuSizeWindow, NULL, SDL_GetWindowSurface(window), NULL);
                    SDL_UpdateWindowSurface(window);
                }

            }

        }

        if (SDL_GetQueuedAudioSize(deviceId) == 0) {

            SDL_QueueAudio(deviceId, wavBuffer, wavLength);

        }
    }
}