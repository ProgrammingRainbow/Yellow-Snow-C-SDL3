#include "flake.h"

bool flake_new(struct Flake **flakes, SDL_Renderer *renderer,
               SDL_Texture *image, bool is_white) {

    struct Flake *new_flake = calloc(1, sizeof(struct Flake));
    if (!new_flake) {
        fprintf(stderr, "Error in calloc of new flake!\n");
        return false;
    }

    new_flake->renderer = renderer;
    new_flake->image = image;
    new_flake->is_white = is_white;

    if (!SDL_GetTextureSize(new_flake->image, &new_flake->rect.w,
                            &new_flake->rect.h)) {
        fprintf(stderr, "Error getting Texture size: %s\n", SDL_GetError());
        return false;
    }

    flake_reset(new_flake, true);

    if (*flakes) {
        new_flake->next = *flakes;
    } else {
        new_flake->next = NULL;
    }
    *flakes = new_flake;

    return true;
}

void flakes_free(struct Flake **flakes) {
    if (*flakes) {
        struct Flake *f = *flakes;

        while (f) {
            f->image = NULL;
            f->renderer = NULL;

            struct Flake *next = f->next;
            free(f);
            f = next;
        }

        *flakes = NULL;

        printf("Free Flakes.\n");
    }
}

void flake_reset(struct Flake *f, bool full) {
    int height = full ? WINDOW_HEIGHT * 2 : WINDOW_HEIGHT;

    f->rect.x = (float)(rand() % (WINDOW_WIDTH - (int)f->rect.w));
    f->rect.y = -(float)(rand() % (height - (int)f->rect.h));
}

void flakes_reset(struct Flake *f, bool full) {
    while (f) {
        flake_reset(f, full);
        f = f->next;
    }
}

float flake_left(const struct Flake *f) { return f->rect.x; }

float flake_right(const struct Flake *f) { return f->rect.x + f->rect.w; }

float flake_bottom(const struct Flake *f) { return f->rect.y + f->rect.h; }

void flakes_update(struct Flake *f, float dt) {
    while (f) {
        f->rect.y += FLAKE_SPEED * dt;

        if (f->rect.y > GROUND) {
            flake_reset(f, false);
        }

        f = f->next;
    }
}

void flakes_draw(const struct Flake *f) {
    while (f) {
        SDL_RenderTexture(f->renderer, f->image, NULL, &f->rect);
        f = f->next;
    }
}
