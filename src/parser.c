/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"
#include "radar.h"

static
int parse_plane(rf_t *rf, char *buffer)
{
    sfVector2f pos = { 0 };
    size_t i = 0;

    buffer++;
    if (!isdigit(*buffer) && !isblank(*buffer))
        return RETURN_FAILURE;
    for (; isblank(*buffer); buffer++);
    if (!isdigit(*buffer))
        return RETURN_FAILURE;
    pos.x = (float)my_getnbr(buffer);
    for (; !isblank(*buffer) && *buffer != '\0'; buffer++);
    buffer++;
    if (!isdigit(*buffer) || *buffer == '\0')
        return RETURN_FAILURE;
    pos.y = (float)my_getnbr(buffer);
    MY_DEBUG("Plane #%01d start pos: %01d, %01d\n", rf->planes_nb, (int)pos.x,
        (int)pos.y);
    rf->planes_nb++;
    i = rf->planes_nb;
    rf->planes[i].pos = pos;
    rf->planes[i].end_pos = (sfVector2f){ 500, 300 };
    rf->planes[i].rotation = atan2f(rf->planes[i].end_pos.y - pos.y,
        rf->planes[i].end_pos.x - pos.x);
    rf->planes[i].active = sfTrue;
    return RETURN_SUCCESS;
}

static
int parse_tower(rf_t *rf, char *buffer)
{
    sfVector2f pos = { 0 };

    buffer++;
    if (!isdigit(*buffer) && !isblank(*buffer))
        return RETURN_FAILURE;
    for (; isblank(*buffer); buffer++);
    if (!isdigit(*buffer))
        return RETURN_FAILURE;
    pos.x = (float)my_getnbr(buffer);
    for (; !isblank(*buffer) && *buffer != '\0'; buffer++);
    buffer++;
    if (!isdigit(*buffer) || *buffer == '\0')
        return RETURN_FAILURE;
    pos.y = (float)my_getnbr(buffer);
    MY_DEBUG("Tower #%01d start pos: %01d, %01d\n", rf->towers_nb, (int)pos.x,
        (int)pos.y);
    rf->towers_nb++;
    rf->towers->pos = pos;
    return RETURN_SUCCESS;
}

int parser(rf_t *rf, char *path)
{
    FILE *file = fopen(path, "r");
    char *buffer = NULL;
    size_t buff_size = 100;

    if (!file)
        return FAILURE_MSG("Cannot open script file !");
    for (; getline(&buffer, &buff_size, file) != -1;) {
        MY_DEBUG("Script file: %s", buffer);
        if (*buffer == 'A' && parse_plane(rf, buffer) == RETURN_FAILURE)
            return FAILURE_MSG("Cannot parse plane !");
        if (*buffer == 'T' && parse_tower(rf, buffer) == RETURN_FAILURE)
            return FAILURE_MSG("Cannot parse tower !");
    }
    fclose(file);
    return RETURN_SUCCESS;
}
