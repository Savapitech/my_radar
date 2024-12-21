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
