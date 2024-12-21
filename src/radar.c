/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include <stdbool.h>

#include "lib.h"
#include "radar.h"

static
int destroy_all(rf_t *rf)
{
    sfRenderWindow_destroy(rf->window);
    return RETURN_SUCCESS;
}

int radar(void)
{
    rf_t rf = { 0 };

    if (create_window(R_WINDOW_SIZE, &rf))
        return FAILURE_MSG("Failed to create window.");
    create_sprites(10, "test");
    for (; sfRenderWindow_isOpen(rf.window);) {
        display_all(&rf);
        event_handler(&rf);
    }
    if (destroy_all(&rf))
        return FAILURE_MSG("Failed to destroy.");
    return RETURN_SUCCESS;
}
