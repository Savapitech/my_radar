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
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyL)
            rf->show_hitboxes = !rf->show_hitboxes;
        if (event.type == sfEvtKeyPressed && event.key.code == sfKeyS)
            rf->display_sprites = !rf->display_sprites;
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(rf->window);
    }
    return RETURN_SUCCESS;
}
