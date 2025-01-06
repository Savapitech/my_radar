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
    sfClock *delta_clock = sfClock_create();
    sfTime delta;

    if (!delta_clock)
        return FAILURE_MSG("Cannot create delta clock");
    sfRenderWindow_setFramerateLimit(rf->window, 5);
    for (; sfRenderWindow_isOpen(rf->window);) {
        display_all(rf);
        event_handler(rf);
        delta = sfClock_getElapsedTime(delta_clock);
        move_sprites(rf, rf->planes, rf->planes_nb, (delta.microseconds -
            rf->prev_delta) / 1000000.0);
        rf->prev_delta = delta.microseconds;
    }
    sfClock_destroy(delta_clock);
    return RETURN_SUCCESS;
}

static
int create_background(rf_t *rf, char const *path)
{
    rf->background.sprite = sfSprite_create();
    if (rf->background.sprite == NULL)
        return FAILURE_MSG("Cannot create background sprite");
    rf->background.texture = sfTexture_createFromFile(path, NULL);
    if (rf->background.texture == NULL)
        return FAILURE_MSG("Cannot create background texure");
    sfSprite_setTexture(rf->background.sprite, rf->background.texture, sfTrue);
    return RETURN_SUCCESS;
}

int radar(char **argv)
{
    rf_t rf = { 0, .show_hitboxes = sfFalse };

    if (create_window(R_WINDOW_SIZE, &rf))
        return FAILURE_MSG("Failed to create window.");
    if (parser(&rf, argv[1]) == RETURN_FAILURE)
        return RETURN_FAILURE;
    if (create_tower_hitboxes(rf.towers, rf.towers_nb) == RETURN_FAILURE)
        return RETURN_FAILURE;
    if (create_background(&rf, "assets/img/background.png") == RETURN_FAILURE)
        return RETURN_FAILURE;
    radar_loop(&rf);
    if (destroy_all(&rf))
        return FAILURE_MSG("Failed to destroy.");
    return RETURN_SUCCESS;
}
