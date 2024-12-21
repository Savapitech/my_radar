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
    rf.planes = create_sprites(10000, "assets/img/plane.png");
    if (rf.planes == NULL)
        return RETURN_FAILURE;
    rf.towers = create_sprites(4, "assets/img/tower.png");
    if (rf.towers == NULL)
        return RETURN_FAILURE;
    set_pos_scale(rf.planes, 6000, (sfVector2f){ 10, 10 },
        (sfVector2f){ 0.5, 0.5 });
    for (; sfRenderWindow_isOpen(rf.window);) {
        display_all(&rf);
        event_handler(&rf);
    }
    if (destroy_all(&rf))
        return FAILURE_MSG("Failed to destroy.");
    return RETURN_SUCCESS;
}
