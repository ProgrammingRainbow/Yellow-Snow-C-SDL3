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

    g->hit_sound = Mix_LoadWAV("sounds/hit.ogg");
    if (!g->hit_sound) {
        fprintf(stderr, "Error loading Chunk: %s\n", SDL_GetError());
        return false;
    }

    g->collect_sound = Mix_LoadWAV("sounds/collect.ogg");
    if (!g->collect_sound) {
        fprintf(stderr, "Error loading Chunk: %s\n", SDL_GetError());
        return false;
    }

    g->winter_music = Mix_LoadMUS("music/winter_loop.ogg");
    if (!g->winter_music) {
        fprintf(stderr, "Error loading Music: %s\n", SDL_GetError());
        return false;
    }

    return true;
}
