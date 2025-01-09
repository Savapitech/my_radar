/*
** EPITECH PROJECT, 2025
** __
** File description:
** _
*/

#include <SFML/Graphics.h>

#include "radar.h"

sfText *create_text(sfVector2f pos, sfVector2f scale, char const *base_text,
    sfColor color)
{
    sfFont *font = sfFont_createFromFile(R_TIMER_FONT_PATH);
    sfText *text;

    if (font == NULL)
        return FAILURE_MSG_PTR("Cannot load text font !");
    text = sfText_create();
    if (text == NULL)
        return FAILURE_MSG_PTR("Cannot create text !");
    sfText_setFont(text, font);
    sfText_setPosition(text, pos);
    sfText_setColor(text, color);
    sfText_setScale(text, scale);
    sfText_setString(text, base_text);
    return text;
}
