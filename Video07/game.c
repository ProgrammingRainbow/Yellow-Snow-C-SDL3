#include "game.h"
#include "init_sdl.h"
#include "load_media.h"

bool game_reset(struct Game *g);
bool handle_collision(struct Game *g, struct Flake *f);
bool check_collision(struct Game *g);
bool game_toggle_music(struct Game *g);
bool game_events(struct Game *g);
bool game_update(struct Game *g);
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

    srand((unsigned)time(NULL));

    for (unsigned int i = 0; i < WHITE_FLAKES; i++) {
        if (!flake_new(&g->flakes, g->renderer, g->white_image, true)) {
            return false;
        }
    }

    for (unsigned int i = 0; i < YELLOW_FLAKES; i++) {
        if (!flake_new(&g->flakes, g->renderer, g->yellow_image, false)) {
            return false;
        }
    }

    if (!score_new(&g->score, g->renderer)) {
        return false;
    }

    g->is_running = true;
    g->is_playing = true;

    return true;
}

void game_free(struct Game **game) {
    if (*game) {
        struct Game *g = *game;

        Mix_HaltMusic();
        Mix_HaltChannel(-1);

        if (g->winter_music) {
            Mix_FreeMusic(g->winter_music);
            g->winter_music = NULL;
        }
        if (g->collect_sound) {
            Mix_FreeChunk(g->collect_sound);
            g->collect_sound = NULL;
        }
        if (g->hit_sound) {
            Mix_FreeChunk(g->hit_sound);
            g->hit_sound = NULL;
        }

        if (g->score) {
            score_free(&g->score);
        }
        if (g->flakes) {
            flakes_free(&g->flakes);
        }
        if (g->player) {
            player_free(&g->player);
        }

        if (g->yellow_image) {
            SDL_DestroyTexture(g->yellow_image);
            g->yellow_image = NULL;
        }
        if (g->white_image) {
            SDL_DestroyTexture(g->white_image);
            g->white_image = NULL;
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

        Mix_Quit();
        TTF_Quit();
        SDL_Quit();

        free(g);
        g = NULL;
        *game = NULL;

        printf("All clean!\n");
    }
}

bool game_reset(struct Game *g) {
    if (!g->is_playing) {
        flakes_reset(g->flakes, true);

        if (!score_reset(g->score)) {
            return false;
        }

        if (!g->is_muted) {
            if (!Mix_PlayMusic(g->winter_music, -1)) {
                fprintf(stderr, "Error while playing music: %s\n",
                        SDL_GetError());
                return false;
            }
        }

        g->is_playing = true;
    }

    return true;
}

bool handle_collision(struct Game *g, struct Flake *f) {
    if (f->is_white) {
        flake_reset(f, false);
        Mix_PlayChannel(-1, g->collect_sound, 0);
        if (!score_increment(g->score)) {
            return false;
        }
    } else {
        Mix_HaltMusic();
        Mix_PlayChannel(-1, g->hit_sound, 0);
        g->is_playing = false;
    }

    return true;
}

bool check_collision(struct Game *g) {
    struct Flake *f = g->flakes;

    while (f) {
        if (flake_bottom(f) > player_top(g->player)) {
            if (flake_right(f) > player_left(g->player)) {
                if (flake_left(f) < player_right(g->player)) {
                    if (!handle_collision(g, f)) {
                        return false;
                    }
                }
            }
        }

        f = f->next;
    }

    return true;
}

bool game_toggle_music(struct Game *g) {
    if (g->is_muted) {
        g->is_muted = false;
        if (g->is_playing) {
            if (Mix_PausedMusic() && Mix_PlayingMusic()) {
                Mix_ResumeMusic();
            } else {
                if (!Mix_PlayMusic(g->winter_music, -1)) {
                    fprintf(stderr, "Error playing Music: %s\n",
                            SDL_GetError());
                    return false;
                }
            }
        }
    } else {
        g->is_muted = true;
        if (!Mix_PausedMusic()) {
            Mix_PauseMusic();
        }
    }

    return true;
}

bool game_events(struct Game *g) {
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
            case SDL_SCANCODE_SPACE:
                if (!game_reset(g)) {
                    return false;
                }
                break;
            case SDL_SCANCODE_M:
                game_toggle_music(g);
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    }

    return true;
}

bool game_update(struct Game *g) {
    if (g->is_playing) {
        player_update(g->player);
        flakes_update(g->flakes);
        if (!check_collision(g)) {
            return false;
        }
    }

    return true;
}

void game_draw(const struct Game *g) {
    SDL_RenderClear(g->renderer);

    SDL_RenderTexture(g->renderer, g->background, NULL, NULL);
    player_draw(g->player);
    flakes_draw(g->flakes);
    score_draw(g->score);

    SDL_RenderPresent(g->renderer);
}

bool game_run(struct Game *g) {
    if (!Mix_PlayMusic(g->winter_music, -1)) {
        fprintf(stderr, "Error playing Music: %s\n", SDL_GetError());
        return false;
    }

    while (g->is_running) {
        game_events(g);

        if (!game_update(g)) {
            return false;
        }

        game_draw(g);

        SDL_Delay(16);
    }

    return true;
}
