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

    if (!clock1)
        return FAILURE_MSG("Cannot create clock");
    for (; sfRenderWindow_isOpen(rf->window);) {
        display_all(rf);
        event_handler(rf);
        if (MICRO_TO_SEC(sfClock_getElapsedTime(clock1)) > 0.001) {
            move_sprites(rf->planes, 1000, (sfVector2f){ 1, 0 });
            sfClock_restart(clock1);
        }
    }
    sfClock_destroy(clock1);
    return RETURN_SUCCESS;
}

int radar(void)
{
    rf_t rf = { 0 };

    if (create_window(R_WINDOW_SIZE, &rf))
        return FAILURE_MSG("Failed to create window.");
    rf.planes = create_sprites(1000, "assets/img/plane.png");
    if (rf.planes == NULL)
        return RETURN_FAILURE;
    rf.towers = create_sprites(4, "assets/img/tower.png");
    if (rf.towers == NULL)
        return RETURN_FAILURE;
    radar_loop(&rf);
    if (destroy_all(&rf))
        return FAILURE_MSG("Failed to destroy.");
    return RETURN_SUCCESS;
}
