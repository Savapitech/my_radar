/*
** EPITECH PROJECT, 2024
** radar
** File description:
** _
*/

#include <SFML/Graphics.h>
#include <math.h>

#include "radar.h"

int set_pos_scale(sprite_t *sprites, size_t nb, sfVector2f pos,
    sfVector2f scale)
{
    if (sprites == NULL || nb < 1)
        return FAILURE_MSG("Cannot set scale/pos of sprite");
    for (size_t i = 0; i < nb; i++) {
        if (sprites[i].sprite == NULL)
            continue;
        sfSprite_setPosition(sprites[i].sprite, pos);
        if (scale.y && scale.x) {
            sfSprite_setScale(sprites[i].sprite, scale);
        }
    }
    return RETURN_SUCCESS;
}

bool plane_in_tower_area(rf_t *rf, size_t plane_i)
{
    double distance = 0;
    sfVector2f plane_pos = rf->planes[plane_i].pos;
    sfVector2f tower_pos = { 0 };

    for (size_t i = 0; i < rf->towers_nb; i++) {
        tower_pos = rf->towers[i].pos;
        distance = sqrt((double)pow(plane_pos.x - tower_pos.x, 2) +
            (double)pow(plane_pos.y - tower_pos.y, 2));
        MY_DEBUG("Plane pos x2: %01f y2: %01f\n", plane_pos.x, plane_pos.y);
        MY_DEBUG("Tower pos x1: %01f y1: %01f\n", tower_pos.x, tower_pos.y);
        MY_DEBUG("Plane #%01d distance to tower #%01d: %01f\n", plane_i, i,
            distance);
        if (distance < rf->towers[i].radius)
            return true;
    }
    return false;
}

static
void move_sprites_set_pos(sprite_t *sprites, size_t i)
{
    sfSprite_setRotation(sprites[i].sprite, sprites[i].rotation * 180 /
        M_PI);
    sfSprite_setPosition(sprites[i].sprite, sprites[i].pos);
    sfRectangleShape_setPosition(sprites[i].hitbox, sprites[i].pos);
    sfRectangleShape_setRotation(sprites[i].hitbox, sprites[i].rotation *
        180 / M_PI);
}

int move_sprites(rf_t *rf, sprite_t *sprites, size_t nb, float delta)
{
    if (sprites == NULL || nb < 1)
        return FAILURE_MSG("Cannot set scale/pos of sprite");
    for (size_t i = 0; i < nb; i++) {
        if (sprites[i].sprite == NULL || !sprites[i].active)
            continue;
        sprites[i].pos.x += cosf(sprites[i].rotation) * 100.0 * delta;
        sprites[i].pos.y += sinf(sprites[i].rotation) * 100.0 * delta;
        if (!sprites[i].active || (sprites[i].pos.x - sprites[i].end_pos.x < 1
            && sprites[i].pos.y - sprites[i].end_pos.y < 1)) {
            sprites[i].active = sfFalse;
            continue;
        }
        move_sprites_set_pos(sprites, i);
        if (plane_in_tower_area(rf, i))
            sfRectangleShape_setOutlineColor(rf->planes[i].hitbox,
                sfGreen);
        else
            sfRectangleShape_setOutlineColor(rf->planes[i].hitbox,
                sfRed);
    }
    return RETURN_SUCCESS;
}
