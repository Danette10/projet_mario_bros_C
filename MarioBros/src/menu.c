#include <SDL.h>
#include "../include/headers/menu.h"
#include "../include/headers/game.h"
#include "../include/headers/utilities.h"


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

// Write text on the screen
void writeTextOnScreen(char *text, int x, int y, int size, SDL_Renderer *renderer) {

    if (TTF_Init() != 0)
    {
        fprintf(stderr, "Erreur d'initialisation TTF : %s\n", TTF_GetError());
    }

    TTF_Font * font1;
    font1 = TTF_OpenFont("../include/ressources/fonts/Raleway.ttf", size);

    SDL_Color color1 = {0, 0, 0};
    SDL_Surface * surface1 = TTF_RenderText_Blended(font1, text, color1);
    SDL_Texture * texture1 = SDL_CreateTextureFromSurface(renderer, surface1);

    SDL_Rect rect1;
    rect1.x = x;
    rect1.y = y;
    rect1.w = 20;
    rect1.h = 50;

    SDL_RenderCopy(renderer, texture1, NULL, &rect1);
    SDL_RenderPresent(renderer);

    // Ne pas prendre en compte les events de la souris
    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);

    TTF_CloseFont(font1);

    SDL_FreeSurface(surface1);

    SDL_DestroyTexture(texture1);

    TTF_Quit();

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

    DIR* dir = opendir("../include/ressources/scores");

    // Afficher une image de mort pour illustrer le nombre de morts
    SDL_Rect rect;
    rect.x = 10;
    rect.y = 90;
    rect.w = 30;
    rect.h = 30;
    SDL_Surface *death = SDL_LoadBMP("../include/ressources/images/menu/death.bmp");
    SDL_Texture *textureDeath = SDL_CreateTextureFromSurface(renderer, death);
    SDL_RenderCopy(renderer, textureDeath, NULL, &rect);
    SDL_RenderPresent(renderer);

    if (dir) {

        int text = readTextFile("../include/ressources/scores/deaths.txt");

        // Si le fichier n'existe pas, on affiche 0

        if(text == -1){
            text = 0;
        }
        char text2[100];

        sprintf(text2, "%d", text);
        writeTextOnScreen(text2, 50, 80, 80, renderer);

    }else{

        writeTextOnScreen("0", 50, 80, 80, renderer);

    }
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

                        loopGame(renderer);

                        break;

                    case 3:

                        SDL_Quit();
                        exit(0);

                }

                break;
        }
    }

    displayMenu(menu, renderer);
}

