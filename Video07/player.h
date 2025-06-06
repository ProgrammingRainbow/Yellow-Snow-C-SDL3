#ifndef PLAYER_H
#define PLAYER_H

#include "main.h"

struct Player {
        SDL_Renderer *renderer;
        SDL_Texture *image;
        SDL_FRect rect;
        const bool *keystate;
        SDL_FlipMode flip;
};

bool player_new(struct Player **player, SDL_Renderer *renderer,
                SDL_Texture *image);
void player_free(struct Player **player);
float player_left(const struct Player *p);
float player_right(const struct Player *p);
float player_top(const struct Player *p);
void player_update(struct Player *p);
void player_draw(const struct Player *p);

#endif
