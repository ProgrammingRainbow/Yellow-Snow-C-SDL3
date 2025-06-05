#include "game.h"
#include "init_sdl.h"
#include "load_media.h"

void game_events(struct Game *g);
void game_update(struct Game *g);
void game_draw(const struct Game *g);

bool game_new(struct Game **game) {
    *game = calloc(1, sizeof(struct Game));
    if (*game == NULL) {
        fprintf(stderr, "Error in Calloc of New Game.\n");
        return false;
    }
    struct Game *g = *game;

    if (!game_init_sdl(g)) {
        return false;
    }
    if (!game_load_media(g)) {
        return false;
    }

    if (!player_new(&g->player, g->renderer, g->player_image)) {
        return false;
    }

    g->is_running = true;

    return true;
}

void game_free(struct Game **game) {
    if (*game) {
        struct Game *g = *game;

        if (g->player) {
            player_free(&g->player);
        }

        if (g->player_image) {
            SDL_DestroyTexture(g->player_image);
            g->player_image = NULL;
        }
        if (g->background) {
            SDL_DestroyTexture(g->background);
            g->background = NULL;
        }

        if (g->renderer) {
            SDL_DestroyRenderer(g->renderer);
            g->renderer = NULL;
        }
        if (g->window) {
            SDL_DestroyWindow(g->window);
            g->window = NULL;
        }

        SDL_Quit();

        free(g);
        g = NULL;
        *game = NULL;

        printf("All clean!\n");
    }
}

void game_events(struct Game *g) {
    while (SDL_PollEvent(&g->event)) {
        switch (g->event.type) {
        case SDL_EVENT_QUIT:
            g->is_running = false;
            break;
        case SDL_EVENT_KEY_DOWN:
            switch (g->event.key.scancode) {
            case SDL_SCANCODE_ESCAPE:
                g->is_running = false;
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }
}

void game_update(struct Game *g) { player_update(g->player); }

void game_draw(const struct Game *g) {
    SDL_RenderClear(g->renderer);

    SDL_RenderTexture(g->renderer, g->background, NULL, NULL);
    player_draw(g->player);

    SDL_RenderPresent(g->renderer);
}

void game_run(struct Game *g) {
    while (g->is_running) {
        game_events(g);

        game_update(g);

        game_draw(g);

        SDL_Delay(16);
    }
}
