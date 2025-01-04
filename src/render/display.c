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
    sfRenderWindow_clear(rf->window, sfBlack);
    for (int i = 0; i < 10; i++)
        if (rf->planes[i].active) {
            sfRenderWindow_drawSprite(rf->window, rf->planes[i].sprite, NULL);
            sfRenderWindow_drawRectangleShape(rf->window,
                rf->planes[i].hitbox, NULL);
        }
    sfRenderWindow_display(rf->window);
    return RETURN_SUCCESS;
}
