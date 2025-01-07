/*
** EPITECH PROJECT, 2024
** radar
** File description:
** _
*/

#include <SFML/Graphics.h>
#include <math.h>
#include <stdio.h>

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

int plane_hit_another(sprite_t *planes, size_t i, size_t nb)
{
    size_t j = 0;
    double distance = 0;
    sfVector2f plane1_pos = planes[i].pos;
    sfVector2f plane2_pos = { 0 };

    for (; j < nb; j++) {
        if (j != i && planes[j].active) {
            plane2_pos = planes[j].pos;
            distance = sqrt((double)pow(plane1_pos.x - plane2_pos.x, 2) +
                (double)pow(plane1_pos.y - plane2_pos.y, 2));
            if (distance < 22) {
                planes[i].active = sfFalse;
                planes[j].active = sfFalse;
                return (j);
            }
        }
    }
    return -1;
}

static
void move_sprites_set_pos(sprite_t *sprites, size_t i)
{
    sfSprite_setOrigin(sprites[i].sprite, (sfVector2f){ 0, 0 });
    sfSprite_setRotation(sprites[i].sprite, sprites[i].rotation * 180 /
        M_PI);
    sfSprite_setPosition(sprites[i].sprite, (sfVector2f){
        sprites[i].pos.x, sprites[i].pos.y });
    sfRectangleShape_setOrigin(sprites[i].hitbox, (sfVector2f){ 10, 10 });
    sfRectangleShape_setPosition(sprites[i].hitbox, (sfVector2f){
        sprites[i].pos.x, sprites[i].pos.y });
    sfRectangleShape_setRotation(sprites[i].hitbox, sprites[i].rotation *
        180 / M_PI);
}

static
bool calc_plane_pos(rf_t *rf, sfClock *delta_clock, size_t i, float delta)
{
    sprite_t *sprites = rf->planes;

    if (sprites[i].time_to_take_off >
        sfClock_getElapsedTime(delta_clock).microseconds / 1000000.0 ||
        sprites[i].sprite == NULL || !sprites[i].active)
            return true;
    sprites[i].taked_off = sfTrue;
    sprites[i].pos.x += cosf(sprites[i].rotation) * sprites[i].speed *
        delta;
    sprites[i].pos.y += sinf(sprites[i].rotation) * sprites[i].speed *
        delta;
    if (!sprites[i].active || (sprites[i].pos.x - sprites[i].end_pos.x < 1
        && sprites[i].pos.y - sprites[i].end_pos.y < 1)) {
        sprites[i].active = sfFalse;
            return true;
    }
    move_sprites_set_pos(sprites, i);
    return false;
}

int move_sprites(rf_t *rf, size_t nb, sfClock *delta_clock, float delta)
{
    sprite_t *sprites = rf->planes;

    if (sprites == NULL || nb < 1)
        return FAILURE_MSG("Cannot set pos of sprite");
    for (size_t i = 0; i < nb; i++) {
        if (calc_plane_pos(rf, delta_clock, i, delta))
            continue;
        if (plane_in_tower_area(rf, i)) {
            sfRectangleShape_setOutlineColor(rf->planes[i].hitbox,
                sfGreen);
            continue;
        }
        sfRectangleShape_setOutlineColor(rf->planes[i].hitbox,
            sfRed);
        if (plane_hit_another(sprites, i, rf->planes_nb) != -1) {
            rf->planes[i].active = sfFalse;
            my_printf("Plane #%01d hit a plane !\n", i);
        }
    }
    return RETURN_SUCCESS;
}
