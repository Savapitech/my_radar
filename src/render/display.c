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
    return RETURN_SUCCESS;
}
