#ifndef GAME_H
#define GAME_H

#include "flake.h"
#include "fps.h"
#include "main.h"
#include "player.h"
#include "score.h"

struct Game {
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *background;
        SDL_Texture *player_image;
        SDL_Texture *white_image;
        SDL_Texture *yellow_image;
        Mix_Music *winter_music;
        Mix_Chunk *collect_sound;
        Mix_Chunk *hit_sound;
        struct Player *player;
        struct Flake *flakes;
        struct Score *score;
        struct Fps *fps;
        SDL_Event event;
        bool is_running;
        bool is_playing;
        bool is_muted;
        float dt;
};

bool game_new(struct Game **game);
void game_free(struct Game **game);
bool game_run(struct Game *g);

#endif
