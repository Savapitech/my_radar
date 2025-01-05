/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include <SFML/Graphics.h>

#include "radar.h"

static
void display_planes(rf_t *rf, size_t i)
{
    sfRenderWindow_drawSprite(rf->window, rf->planes[i].sprite, NULL);
    if (rf->show_hitboxes)
        sfRenderWindow_drawRectangleShape(rf->window,
            rf->planes[i].hitbox, NULL);
}

int display_all(rf_t *rf)
{
    sfRenderWindow_clear(rf->window, sfBlack);
    sfRenderWindow_drawSprite(rf->window, rf->background.sprite, NULL);
    for (size_t i = 0; i < rf->planes_nb; i++)
        if (rf->planes[i].active)
            display_planes(rf, i);
    for (size_t i = 0; i < rf->towers_nb; i++) {
        sfRenderWindow_drawSprite(rf->window, rf->towers[i].sprite, NULL);
        if (rf->show_hitboxes)
            sfRenderWindow_drawCircleShape(rf->window,
                rf->towers[i].t_hitbox, NULL);
    }
    sfRenderWindow_display(rf->window);
    return RETURN_SUCCESS;
}
