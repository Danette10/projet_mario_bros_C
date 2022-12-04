#include <stdio.h>
#include <stdlib.h>
#include <SDL_audio.h>
#include <SDL_video.h>
#include <SDL.h>

const int WIDTH = 1000, HEIGHT = 800;

int main(int argc, char *argv[]) {
    SDL_Window *window;
    //SDL_Renderer *renderer;
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

        }

        if (SDL_GetQueuedAudioSize(deviceId) == 0) {

            SDL_QueueAudio(deviceId, wavBuffer, wavLength);

        }
    }
}