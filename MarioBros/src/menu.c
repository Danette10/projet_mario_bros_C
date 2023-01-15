#include <SDL.h>
#include "../include/headers/menu.h"
#include "../include/headers/game.h"


// Initialize a new menu with a given number of options
void initMenu(Menu *menu, int optionCount) {
    menu->options = (char**)malloc(sizeof(char*) * optionCount);
    menu->optionCount = optionCount;
    menu->currentIndex = 0;
}

// Add an option (BMP file) to the menu
void addOption(Menu *menu, char *option, int index) {
    menu->options[index] = option;
}

// Display the menu on the screen using the provided renderer
void displayMenu(Menu *menu, Renderer *renderer) {
    // Load the current option's image
    SDL_Surface *currentOption = SDL_LoadBMP(menu->options[menu->currentIndex]);

    // Create a texture from the image
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, currentOption);
    if (texture == NULL) {
        printf("Could not create texture: %s\n", SDL_GetError());
        return;
    }

    // Display the texture in the window
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    // Free the memory
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(currentOption);
}

// Function to delete the menu
void deleteMenu(Menu *menu) {

    free(menu->options);
    menu->options = NULL;
    menu->optionCount = 0;
    menu->currentIndex = 0;

}

void handleMenuNavigation(Menu *menu, Renderer *renderer, SDL_Event *event) {
    // Handle arrow key presses for menu navigation
    if (event->type == SDL_KEYDOWN) {

        switch (event->key.keysym.sym) {

            case SDLK_UP:

                if (menu->currentIndex > 0) {

                    menu->currentIndex--;

                } else {

                    menu->currentIndex = menu->optionCount - 1;
                }

                break;

            case SDLK_DOWN:

                if (menu->currentIndex < menu->optionCount - 1) {

                    menu->currentIndex++;

                } else {

                    menu->currentIndex = 0;

                }

                break;

            case SDLK_RETURN:
            case SDLK_SPACE:

                switch (menu->currentIndex) {

                    case 0:

                        // Suppression du menu
                        deleteMenu(menu);

                        // Création du background
                        createBackground(renderer, "../include/ressources/images/background/desert/desert1.bmp", 0, 0, WIDTH, HEIGHT);

                        // Creation du joueur
                        createPlayer(renderer, "../include/ressources/images/sprite/mario/mario_normal_1.bmp");

                        break;

                }

                break;
        }
    }

    displayMenu(menu, renderer);
}

