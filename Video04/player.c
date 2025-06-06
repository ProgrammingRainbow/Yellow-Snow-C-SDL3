#include "player.h"

bool player_new(struct Player **player, SDL_Renderer *renderer,
                SDL_Texture *image) {
    *player = calloc(1, sizeof(struct Player));
    if (*player == NULL) {
        fprintf(stderr, "Error Calloc of New Player.\n");
        return false;
    }
    struct Player *p = *player;

    p->renderer = renderer;
    p->image = image;

    if (!SDL_GetTextureSize(p->image, &p->rect.w, &p->rect.h)) {
        fprintf(stderr, "Error getting Texture Size: %s\n", SDL_GetError());
        return false;
    }

    p->rect.x = (float)(WINDOW_WIDTH - p->rect.w) / 2;
    p->rect.y = PLAYER_Y;

    p->keystate = SDL_GetKeyboardState(NULL);

    return true;
}

void player_free(struct Player **player) {
    if (*player) {
        struct Player *p = *player;

        if (p->image) {
            SDL_DestroyTexture(p->image);
            p->image = NULL;
        }

        p->renderer = NULL;
        p->keystate = NULL;

        free(p);
        p = NULL;
        *player = NULL;

        printf("Free Player.\n");
    }
}

void player_update(struct Player *p) {
    if (p->keystate[SDL_SCANCODE_LEFT] || p->keystate[SDL_SCANCODE_A]) {
        p->rect.x -= PLAYER_VEL;
        if (p->rect.x + PLAYER_LEFT_OFFSET < 0) {
            p->rect.x = -PLAYER_LEFT_OFFSET;
        }
        p->flip = SDL_FLIP_HORIZONTAL;
    }
    if (p->keystate[SDL_SCANCODE_RIGHT] || p->keystate[SDL_SCANCODE_D]) {
        if (p->rect.x + p->rect.w - PLAYER_RIGHT_OFFSET > WINDOW_WIDTH) {
            p->rect.x = WINDOW_WIDTH + PLAYER_RIGHT_OFFSET - p->rect.w;
        }
        p->rect.x += PLAYER_VEL;
        p->flip = SDL_FLIP_NONE;
    }
}

void player_draw(const struct Player *p) {
    SDL_RenderTextureRotated(p->renderer, p->image, NULL, &p->rect, 0, NULL,
                             p->flip);
}
