/*
** EPITECH PROJECT, 2024
** radar
** File description:
** _
*/

#include <SFML/Graphics.h>

#include "radar.h"

sprite_t *create_sprites(size_t nb, char const *texture_path)
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
        MY_DEBUG("Set sprite #%01d positon to %01d, %01d\n", i, pos.x, pos.y);
        if (scale.y && scale.x) {
            sfSprite_setScale(sprites[i].sprite, scale);
            MY_DEBUG("Set sprite #%01d scale to %.2f, %.2f\n", i, scale.x,
                scale.y);
        }
    }
    return RETURN_SUCCESS;
}

int move_sprites(sprite_t *sprites, size_t nb, sfVector2f pos)
{
    if (sprites == NULL || nb < 1)
        return FAILURE_MSG("Cannot set scale/pos of sprite");
    for (size_t i = 0; i < nb; i++) {
        if (sprites[i].sprite == NULL)
            continue;
        sfSprite_move(sprites[i].sprite, pos);
        MY_DEBUG("Set sprite #%01d positon to %01d, %01d\n", i, pos.x, pos.y);
    }
    return RETURN_SUCCESS;
}
