#include <SDL_video.h>

void cutTileset(SDL_Renderer* renderer, const char* tileset, int tileWidth, int tileHeight, int tileCount) {
    // Load the tileset image
    SDL_Surface* tilesetSurface = SDL_LoadBMP(tileset);
    if (!tilesetSurface) {
        fprintf(stderr, "Failed to load tileset image: %s\n", SDL_GetError());
        return;
    }

    // Cut the tileset into individual tile images
    SDL_Rect srcRect;
    srcRect.w = tileWidth;
    srcRect.h = tileHeight;
    for (int i = 0; i < tileCount; i++) {
        srcRect.x = i * tileWidth;
        srcRect.y = 0;

        SDL_Surface* tileSurface = SDL_CreateRGBSurface(0, tileWidth, tileHeight, 32, 0, 0, 0, 0);
        SDL_BlitSurface(tilesetSurface, &srcRect, tileSurface, NULL);

        char filename[32];
        sprintf(filename, "../include/ressources/images/tileset/tile%d.bmp", i);
        SDL_SaveBMP(tileSurface, filename);
        SDL_FreeSurface(tileSurface);
    }

    SDL_FreeSurface(tilesetSurface);
}