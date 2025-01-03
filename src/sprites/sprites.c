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
        if (sprites[i].pos.x - sprites[i].end_pos.x < 1 &&
            sprites[i].pos.y - sprites[i].end_pos.y < 1) {
            sprites[i].active = sfFalse;
            continue;
        } 
        sfSprite_setPosition(sprites[i].sprite, sprites[i].pos);
        MY_DEBUG("Move plane to %0.1f, %0.1f %f\n", sprites[i].pos.x,
            sprites[i].pos.y, delta);
    }
    return RETURN_SUCCESS;
}
