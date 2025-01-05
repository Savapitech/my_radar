/*
** EPITECH PROJECT, 2024
** radar
** File description:
** _
*/

#include <SFML/Graphics.h>
#include <math.h>

#include "radar.h"

sprite_t *create_sprites(size_t nb, char const *texture_path, sfVector2f scale)
{
    sfTexture *texture;
    sprite_t *sprites = malloc(sizeof(sprite_t) * nb);

    if (sprites == NULL)
        return FAILURE_MSG_PTR("Cannot malloc when creating sprites");
    texture = sfTexture_createFromFile(texture_path, NULL);
    if (texture == NULL)
        return (free(sprites), NULL);
    for (size_t i = 0; i < nb; i++) {
        sprites[i] = (sprite_t){ 0, .active = sfTrue };
        sprites[i].texture = texture;
        sprites[i].sprite = sfSprite_create();
        if (sprites[i].sprite == NULL)
            return (free(sprites), FAILURE_MSG_PTR("Can't create sprite"));
        sfSprite_setTexture(sprites[i].sprite, sprites[i].texture, sfTrue);
        sfSprite_setScale(sprites[i].sprite, scale);
    }
    MY_DEBUG("%d sprites created with texture %s\n", nb, texture_path);
    return sprites;
}

int create_plane_hitboxes(sprite_t *sprites, size_t nb)
{
    if (sprites == NULL)
        return FAILURE_MSG("Sprites is null when creating plane hitbox");
    for (size_t i = 0; i < nb; i++) {
        sprites[i].hitbox = sfRectangleShape_create();
        if (sprites[i].hitbox == NULL)
            return FAILURE_MSG("Cannot create rect shape for plane hitbox");
        sfRectangleShape_setFillColor(sprites[i].hitbox, sfTransparent);
        sfRectangleShape_setOutlineColor(sprites[i].hitbox, sfRed);
        sfRectangleShape_setOutlineThickness(sprites[i].hitbox, 1.0);
        sfRectangleShape_setSize(sprites[i].hitbox, (sfVector2f){ 20, 20 });
        sfRectangleShape_setPosition(sprites[i].hitbox, sprites[i].pos);
    }
    return RETURN_SUCCESS;
}

int create_tower_hitboxes(sprite_t *sprites, size_t nb)
{
    if (sprites == NULL)
        return FAILURE_MSG("Sprites is null when creating tower hitbox");
    for (size_t i = 0; i < nb; i++) {
        sprites[i].t_hitbox = sfCircleShape_create();
        if (sprites[i].t_hitbox == NULL)
            return FAILURE_MSG("Cannot create circle shape for tower hitbox");
        sfCircleShape_setFillColor(sprites[i].t_hitbox, sfTransparent);
        sfCircleShape_setOutlineColor(sprites[i].t_hitbox, sfBlue);
        sfCircleShape_setOutlineThickness(sprites[i].t_hitbox, 1.0);
        sfCircleShape_setRadius(sprites[i].t_hitbox, sprites[i].radius);
        sfCircleShape_setPosition(sprites[i].t_hitbox,
            (sfVector2f){ sprites[i].pos.x - sprites[i].radius,
            sprites[i].pos.y - sprites[i].radius });
    }
    return RETURN_SUCCESS;
}

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

int move_sprites(sprite_t *sprites, size_t nb, float delta)
{
    if (sprites == NULL || nb < 1)
        return FAILURE_MSG("Cannot set scale/pos of sprite");
    for (size_t i = 0; i < nb; i++) {
        if (sprites[i].sprite == NULL)
            continue;
        sprites[i].pos.x += cosf(sprites[i].rotation) * 100.0 * delta;
        sprites[i].pos.y += sinf(sprites[i].rotation) * 100.0 * delta;
        if (!sprites[i].active || (sprites[i].pos.x - sprites[i].end_pos.x < 1
            && sprites[i].pos.y - sprites[i].end_pos.y < 1)) {
            sprites[i].active = sfFalse;
            continue;
        }
        sfSprite_setRotation(sprites[i].sprite, sprites[i].rotation * 180 /
            M_PI);
        sfSprite_setPosition(sprites[i].sprite, sprites[i].pos);
        sfRectangleShape_setPosition(sprites[i].hitbox, sprites[i].pos);
        sfRectangleShape_setRotation(sprites[i].hitbox, sprites[i].rotation *
            180 / M_PI);
    }
    return RETURN_SUCCESS;
}
