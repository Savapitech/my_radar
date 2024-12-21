/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include <SFML/Graphics.h>

#include "radar.h"

int display_all(rf_t *rf)
{
    sfRenderWindow_display(rf->window);
    for (int i = 0; i < 10000; i++) {
        sfRenderWindow_drawSprite(rf->window, rf->planes[i].sprite, NULL);
    }
    return RETURN_SUCCESS;
}
