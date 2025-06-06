#ifndef MAIN_H
#define MAIN_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SDL_FLAGS SDL_INIT_VIDEO
#define MIX_FLAGS MIX_INIT_OGG

#define WINDOW_TITLE "Don't Eat the Yellow Snow!"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PLAYER_VEL 300
#define PLAYER_Y 377
#define PLAYER_TOP_OFFSET 10
#define PLAYER_LEFT_OFFSET 47
#define PLAYER_RIGHT_OFFSET 42

#define WHITE_FLAKES 10
#define YELLOW_FLAKES 5
#define FLAKE_SPEED 300
#define GROUND 514

#define FONT_FILE "fonts/freesansbold.ttf"
#define FONT_SIZE 32
#define FONT_COLOR 255, 255, 255, 255
#define SCORE_X 10
#define SCORE_Y 10

#define TARGET_FPS 60
#define MAX_FPS_DELAY 50
#define SHOW_FPS false

#endif
