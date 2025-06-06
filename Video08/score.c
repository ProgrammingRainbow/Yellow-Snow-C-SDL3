#include "score.h"

bool score_update(struct Score *s);

bool score_new(struct Score **score, SDL_Renderer *renderer) {

    *score = calloc(1, sizeof(struct Score));
    if (!*score) {
        fprintf(stderr, "Error in calloc of score!\n");
        return false;
    }
    struct Score *s = *score;

    s->renderer = renderer;

    s->font = TTF_OpenFont(FONT_FILE, FONT_SIZE);
    if (!s->font) {
        fprintf(stderr, "Error creating font: %s\n", SDL_GetError());
        return false;
    }

    s->text_engine = TTF_CreateRendererTextEngine(renderer);
    if (!s->text_engine) {
        fprintf(stderr, "Error creating Text Engine: %s\n", SDL_GetError());
        return false;
    }

    s->text = TTF_CreateText(s->text_engine, s->font, "Score: 0", 0);
    if (!s->text) {
        fprintf(stderr, "Error creating Text: %s\n", SDL_GetError());
        return false;
    }

    if (!TTF_SetTextColor(s->text, FONT_COLOR)) {
        fprintf(stderr, "Error setting Text Color: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void score_free(struct Score **score) {
    if (*score) {
        struct Score *s = *score;

        if (s->text) {
            TTF_DestroyText(s->text);
            s->text = NULL;
        }
        if (s->text_engine) {
            TTF_DestroyRendererTextEngine(s->text_engine);
            s->text_engine = NULL;
        }
        if (s->font) {
            TTF_CloseFont(s->font);
            s->font = NULL;
        }

        s->renderer = NULL;

        free(s);
        s = NULL;
        *score = NULL;

        printf("Free Score.\n");
    }
}

bool score_update(struct Score *s) {

    int length = snprintf(NULL, 0, "Score: %d", s->score) + 1;
    char score_str[length];
    snprintf(score_str, (size_t)length, "Score: %d", s->score);

    if (!TTF_SetTextString(s->text, score_str, 0)) {
        fprintf(stderr, "Error setting Text string: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool score_reset(struct Score *s) {
    s->score = 0;
    if (!score_update(s)) {
        return false;
    }

    return true;
}

bool score_increment(struct Score *s) {
    s->score++;
    if (!score_update(s)) {
        return false;
    }

    return true;
}

void score_draw(const struct Score *s) {
    TTF_DrawRendererText(s->text, SCORE_X, SCORE_Y);
}
