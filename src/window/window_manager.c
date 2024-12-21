/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "radar.h"
#include "lib.h"
#include <SFML/Graphics.h>

int create_window(size_t x, size_t y, rf_t *rf)
{
    sfVideoMode mode = { x, y, 32 };

    rf->window = sfRenderWindow_create(mode,
        R_WINDOW_NAME, sfResize | sfClose, NULL);
    if (!rf->window)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
