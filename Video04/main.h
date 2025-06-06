#ifndef MAIN_H
#define MAIN_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SDL_FLAGS SDL_INIT_VIDEO

#define WINDOW_TITLE "Don't Eat the Yellow Snow!"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PLAYER_VEL 5
#define PLAYER_Y 377
#define PLAYER_TOP_OFFSET 10
#define PLAYER_LEFT_OFFSET 47
#define PLAYER_RIGHT_OFFSET 42

#define WHITE_FLAKES 10
#define YELLOW_FLAKES 5

#endif
