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
    for (size_t i = 0; i < rf->planes_nb; i++)
        if (rf->planes[i].sprite != NULL)
            sfSprite_destroy(rf->planes[i].sprite);
    sfTexture_destroy(rf->planes->texture);
    for (size_t i = 0; i < rf->towers_nb; i++)
        if (rf->towers[i].sprite != NULL)
            sfSprite_destroy(rf->towers[i].sprite);
    sfTexture_destroy(rf->towers->texture);
    sfSprite_destroy(rf->background.sprite);
    sfText_destroy(rf->timer_text);
    sfRenderWindow_destroy(rf->window);
    return RETURN_SUCCESS;
}

static
int radar_loop(rf_t *rf)
{
    sfClock *delta_clock = sfClock_create();
    sfTime delta;
    char score[10];

    if (!delta_clock)
        return FAILURE_MSG("Cannot create delta clock");
    sfRenderWindow_setFramerateLimit(rf->window, 24);
    for (; sfRenderWindow_isOpen(rf->window) && rf->killed_planes <
        rf->planes_nb - 1;) {
        display_all(rf);
        event_handler(rf);
        delta = sfClock_getElapsedTime(delta_clock);
        move_sprites(rf, rf->planes_nb, delta_clock,
            (delta.microseconds - rf->prev_delta) / 1000000.0);
        rf->prev_delta = delta.microseconds;
        my_numstr(score, delta.microseconds / 1000000.0);
        sfText_setString(rf->timer_text, score);
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
    rf_t rf = { 0, .show_hitboxes = sfFalse, .display_sprites = sfTrue };

    if (create_window(R_WINDOW_SIZE, &rf))
        return FAILURE_MSG("Failed to create window.");
    if (parser(&rf, argv[1]) == RETURN_FAILURE)
        return RETURN_FAILURE;
    if (create_tower_hitboxes(rf.towers, rf.towers_nb) == RETURN_FAILURE)
        return RETURN_FAILURE;
    if (create_background(&rf, R_BACKGROUND_TEXTURE_PATH) == RETURN_FAILURE)
        return RETURN_FAILURE;
    rf.timer_text = create_text((sfVector2f){ 1850, 3 }, (sfVector2f){ 1, 1 },
        "0.0", sfWhite);
    if (rf.timer_text == NULL)
        return RETURN_FAILURE;
    radar_loop(&rf);
    if (destroy_all(&rf))
        return FAILURE_MSG("Failed to destroy.");
    return RETURN_SUCCESS;
}
