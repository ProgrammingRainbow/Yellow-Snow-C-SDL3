#ifndef FLAKES_H
#define FLAKES_H

#include "main.h"

struct Flake {
        struct Flake *next;
        SDL_Renderer *renderer;
        SDL_Texture *image;
        SDL_FRect rect;
        bool is_white;
};

bool flake_new(struct Flake **flakes, SDL_Renderer *renderer,
               SDL_Texture *image, bool is_white);
void flakes_free(struct Flake **flakes);
void flake_reset(struct Flake *f);
void flakes_draw(const struct Flake *f);

#endif
