/*
** EPITECH PROJECT, 2024
** radar
** File description:
** _
*/

#ifndef RADAR_H
    #include "colors.h"
    #include "lib.h"
    #include <SFML/Graphics.h>
    #define RADAR_H
    #define OMIT
    #define RETURN_SUCCESS 0
    #define RETURN_FAILURE 84
    #define FAILURE_MSG(str) (my_puterr(str "\n"), RETURN_FAILURE)
    #define FAILURE_MSG_PTR(str) (my_puterr(str "\n"), NULL)
    #define R_WINDOW_NAME "War Thunder Multiplayer"
    #define R_WINDOW_SIZE 1920, 1080
    #define MICRO_TO_SEC(time) time.microseconds / 1000000.0

    #ifdef R_DEBUG_MODE
        #define HEAD __FILE_NAME__, __LINE__

        #define HEAD_FMT_FILE BOLD BLUE "%s" RESET
        #define HEAD_FMT_LINE ":" BOLD PURPLE "%d" RESET

        #define HEAD_FMT HEAD_FMT_FILE HEAD_FMT_LINE "  "

        #define ERR(fmt, ...) my_printf(fmt, __VA_ARGS__)
        #define DEBUG_INTERNAL(fmt, ...) ERR(HEAD_FMT fmt, HEAD, __VA_ARGS__)

        #define MY_DEBUG(fmt, ...) DEBUG_INTERNAL(fmt, __VA_ARGS__)
        #define MY_DEBUG_MSG(msg) DEBUG_INTERNAL("%s\n", msg)
    #else

        #define MY_DEBUG_MSG(msg) OMIT
        #define MY_DEBUG(fmt, ...) OMIT

        #define MY_DEBUG_CALL(func, ...) OMIT
        #define MY_DEBUG_USED __attribute__((unused))
    #endif

typedef struct {
    sfTexture *texture;
    sfSprite *sprite;
    sfRectangleShape *hitbox;
    sfCircleShape *t_hitbox;
    float rotation;
    sfVector2f pos;
    sfVector2f end_pos;
    int speed;
    int time_to_take_off;
    sfVector2u size;
    size_t radius;
    bool taked_off;
    bool active;
} sprite_t;

typedef struct {
    sprite_t *planes;
    sprite_t *towers;
    sprite_t background;
    size_t planes_nb;
    size_t towers_nb;
    size_t killed_planes;
    sfInt64 prev_delta;
    sfRenderWindow *window;
    size_t planes_i;
    size_t towers_i;
    sfText *timer_text;
    bool show_hitboxes;
    bool display_sprites;
} rf_t;

int radar(char **argv);
int parser(rf_t *rf, char *path);

// render
int display_all(rf_t *rf);

// window
int create_window(size_t x, size_t y, rf_t *rf);

// events
int event_handler(rf_t *rf);

// sprites
sprite_t *create_sprites(size_t nb, char const *texture_path,
    sfVector2f scale);
int set_pos_scale(sprite_t *sprites, size_t nb, sfVector2f pos,
    sfVector2f scale);

// text
sfText *create_text(sfVector2f pos, sfVector2f scale, char const *base_text,
    sfColor color);

int move_sprites(rf_t *rf, size_t nb, sfClock *delta_clock, float delta);
int create_plane_hitboxes(sprite_t *sprites, size_t nb);
int create_tower_hitboxes(sprite_t *sprites, size_t nb);
#endif /* RADAR_H */
