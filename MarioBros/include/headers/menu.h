#include <SDL_video.h>
#include "define.h"

typedef struct Menu Menu;
typedef SDL_Renderer Renderer;

struct Menu {
    char **options; // array of BMP file paths for the options
    int optionCount; // number of options in the menu
    int currentIndex; // index of the currently selected option
};

// Initialize a new menu with a given number of options
void initMenu(Menu *menu, int optionCount);

// Add an option (BMP file) to the menu
void addOption(Menu *menu, char *option, int index);

// Display the menu on the screen using the provided renderer
void displayMenu(Menu *menu, Renderer *renderer);

// Handle arrow key presses for menu navigation
void handleMenuNavigation(Menu *menu, Renderer *renderer, SDL_Event *event);

// Function to delete the menu
void deleteMenu(Menu *menu);