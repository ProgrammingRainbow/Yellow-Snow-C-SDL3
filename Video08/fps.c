#include "fps.h"

Uint64 fps_time_since(Uint64 last_time, Uint64 *new_last_time);

bool fps_new(struct Fps **fps) {
    *fps = calloc(1, sizeof(struct Fps));
    if (*fps == NULL) {
        fprintf(stderr, "Error in Calloc of New Fps!\n");
        return false;
    }

    struct Fps *f = *fps;

    f->last_time = SDL_GetTicks();
    f->target_delay = 1000.0 / TARGET_FPS;
    f->carry_delay = 0;
    f->fps_last_time = f->last_time;
    f->fps_counter = 0;
    f->fps_display = false;

    return true;
}

void fps_free(struct Fps **fps) {
    if (*fps) {
        free(*fps);
        *fps = NULL;
    }

    printf("Free FPS.\n");
}

void fps_display_toggle(struct Fps *f) {
    if (f->fps_display) {
        f->fps_display = false;
    } else {
        f->fps_display = true;
        f->fps_counter = 0;
        f->fps_last_time = SDL_GetTicks();
    }
}

Uint64 fps_time_since(Uint64 last_time, Uint64 *new_last_time) {
    Uint64 current_time = SDL_GetTicks();
    Uint64 elapsed_time = 0;

    if (current_time < last_time) {
        elapsed_time = (Uint64)-1 - last_time + current_time;
    } else {
        elapsed_time = current_time - last_time;
    }

    if (new_last_time) {
        *new_last_time = current_time;
    }

    return elapsed_time;
}

float fps_update(struct Fps *f) {
    Uint64 elapsed_time = fps_time_since(f->last_time, NULL);
    double current_delay = f->target_delay + f->carry_delay;

    if (current_delay > elapsed_time) {
        Uint64 delay = (Uint64)current_delay - elapsed_time;
        SDL_Delay((Uint32)delay);
    }

    elapsed_time = fps_time_since(f->last_time, &f->last_time);

    f->carry_delay = current_delay - (double)elapsed_time;
    if (f->carry_delay > MAX_FPS_DELAY) {
        f->carry_delay = MAX_FPS_DELAY;
    } else if (f->carry_delay < -MAX_FPS_DELAY) {
        f->carry_delay = -MAX_FPS_DELAY;
    }

    if (f->fps_display) {
        if (fps_time_since(f->fps_last_time, NULL) >= 1000) {
            printf("%lu\n", f->fps_counter);
            f->fps_counter = 0;
            f->fps_last_time += 1000;
        }
        f->fps_counter++;
    }

    return (float)elapsed_time / 1000;
}
