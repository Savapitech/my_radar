/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include <SFML/Graphics.h>

#include "radar.h"

int event_handler(rf_t *rf)
{
    sfEvent event = { 0 };

    while (sfRenderWindow_pollEvent(rf->window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(rf->window);
    }
    return RETURN_SUCCESS;
}
