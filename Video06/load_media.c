#include "load_media.h"

bool game_load_media(struct Game *g) {
    g->background = IMG_LoadTexture(g->renderer, "images/background.png");
    if (!g->background) {
        fprintf(stderr, "Error loading Texture: %s\n", SDL_GetError());
        return false;
    }

    g->player_image = IMG_LoadTexture(g->renderer, "images/player.png");
    if (!g->player_image) {
        fprintf(stderr, "Error loading Texture: %s\n", SDL_GetError());
        return false;
    }

    g->white_image = IMG_LoadTexture(g->renderer, "images/white.png");
    if (!g->white_image) {
        fprintf(stderr, "Error loading Texture: %s\n", SDL_GetError());
        return false;
    }

    g->yellow_image = IMG_LoadTexture(g->renderer, "images/yellow.png");
    if (!g->yellow_image) {
        fprintf(stderr, "Error loading Texture: %s\n", SDL_GetError());
        return false;
    }

    return true;
}
