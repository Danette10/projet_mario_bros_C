#include <dirent.h>
#include <SDL.h>
#include <SDL_audio.h>

// Function to play music
void playMusic(char *musicPath, int type);

// Function to create a new folder if it doesn't exist
void createFolder(char *folderPath);

// Function to write text in file
void writeTextFile(int text, char *filePath);

// Function to read text in file
int readTextFile(char *filePath);