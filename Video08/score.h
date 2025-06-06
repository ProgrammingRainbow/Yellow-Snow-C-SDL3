#ifndef SCORE_H
#define SCORE_H

#include "main.h"

struct Score {
        SDL_Renderer *renderer;
        TTF_Font *font;
        TTF_Text *text;
        TTF_TextEngine *text_engine;
        int score;
};

bool score_new(struct Score **score, SDL_Renderer *renderer);
void score_free(struct Score **score);
bool score_reset(struct Score *s);
bool score_increment(struct Score *s);
void score_draw(const struct Score *s);

#endif
