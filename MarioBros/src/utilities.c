
#include <SDL.h>
#include <SDL_audio.h>
#include "../include/headers/utilities.h"

// Function to play music
void playMusic(char *musicPath, int type) {

    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8 *wavBuffer;
    SDL_LoadWAV(musicPath, &wavSpec, &wavBuffer, &wavLength);

    SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (deviceId == 0) {
        printf("Failed to open audio: %s \n", SDL_GetError());
        return;
    }

    // Jouer la musique
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);

    if(type == 1){
        while (SDL_GetQueuedAudioSize(deviceId) > 0) {
            SDL_Delay(100);
        }
    }

}

// Function to write text in file
void writeTextFile(int text, char *filePath) {

    FILE *file = fopen(filePath, "w");

    if (file == NULL) {

        printf("Error opening file!\n");

        exit(1);

    }

    fprintf(file, "%d", text);

    fclose(file);

}

// Function to read text in file
int readTextFile(char *filePath) {

    FILE *file = fopen(filePath, "r");

    if (file == NULL) {

        printf("Error opening file!\n");

        return 0;

    }

    int text;

    fscanf(file, "%d", &text);

    fclose(file);

    return text;

}