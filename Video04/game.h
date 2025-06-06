#ifndef GAME_H
#define GAME_H

#include "flake.h"
#include "main.h"
#include "player.h"

struct Game {
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *background;
        SDL_Texture *player_image;
        SDL_Texture *white_image;
        SDL_Texture *yellow_image;
        struct Player *player;
        struct Flake *flakes;
        SDL_Event event;
        bool is_running;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
void game_run(struct Game *g);

#endif
