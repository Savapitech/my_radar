/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include <SFML/System.h>
#include <stdbool.h>

#include "lib.h"
#include "radar.h"

static
int destroy_all(rf_t *rf)
{
    sfRenderWindow_destroy(rf->window);
    return RETURN_SUCCESS;
}

static
int radar_loop(rf_t *rf)
{
    sfClock *clock1 = sfClock_create();
    sfClock *delta_clock = sfClock_create();
    sfTime delta;

    if (!clock1)
        return FAILURE_MSG("Cannot create clock");
    sfRenderWindow_setFramerateLimit(rf->window, 30);
    for (; sfRenderWindow_isOpen(rf->window);) {
        display_all(rf);
        event_handler(rf);
        delta = sfClock_getElapsedTime(delta_clock);
        if (MICRO_TO_SEC(sfClock_getElapsedTime(clock1)) > 0.001) {
            move_sprites(rf->planes, 10, (delta.microseconds -
                rf->prev_delta) / 1000000.0);
            sfClock_restart(clock1);
        }
        rf->prev_delta = delta.microseconds;
    }
    sfClock_destroy(clock1);
    return RETURN_SUCCESS;
}

int radar(char **argv)
{
    rf_t rf = { 0 };

    if (create_window(R_WINDOW_SIZE, &rf))
        return FAILURE_MSG("Failed to create window.");
    rf.planes = create_sprites(10, "assets/img/plane.png",
        (sfVector2f){ 0.07125, 0.07125 });
    if (rf.planes == NULL)
        return RETURN_FAILURE;
    if (create_plane_hitboxes(rf.planes, 10) == RETURN_FAILURE)
        return RETURN_FAILURE;
    rf.towers = create_sprites(4, "assets/img/tower.png",
        (sfVector2f){ 1, 1 });
    if (rf.towers == NULL)
        return RETURN_FAILURE;
    if (parser(&rf, argv[1]) == RETURN_FAILURE)
        return RETURN_FAILURE;
    radar_loop(&rf);
    if (destroy_all(&rf))
        return FAILURE_MSG("Failed to destroy.");
    return RETURN_SUCCESS;
}
