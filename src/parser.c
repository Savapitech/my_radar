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
    size_t i = rf->planes_i;

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
    MY_DEBUG("Plane #%01d start pos: %01d, %01d\n", i, (int)pos.x,
        (int)pos.y);
    rf->planes[i].pos = pos;
    rf->planes[i].end_pos = (sfVector2f){ 500, 300 };
    rf->planes[i].rotation = atan2f(rf->planes[i].end_pos.y - pos.y,
        rf->planes[i].end_pos.x - pos.x);
    rf->planes_i++;
    return RETURN_SUCCESS;
}

static
int parse_tower(rf_t *rf, char *buffer)
{
    sfVector2f pos = { 0 };
    size_t i = rf->towers_i;

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
    MY_DEBUG("Tower #%01d start pos: %01d, %01d\n", i, (int)pos.x,
        (int)pos.y);
    rf->towers[i].pos = pos;
    rf->towers[i].radius = 250;
    rf->towers_i++;
    sfSprite_setPosition(rf->towers[i].sprite, (sfVector2f){ pos.x - 38.4,
        pos.y - 38.4 });
    return RETURN_SUCCESS;
}

static
int count_planes_towers(rf_t *rf, FILE *file)
{
    char *buffer = NULL;
    size_t buff_size = 100;

    if (!file)
        return FAILURE_MSG("Cannot open script file !");
    for (; getline(&buffer, &buff_size, file) != -1;) {
        if (*buffer == 'A')
            rf->planes_nb++;
        if (*buffer == 'T')
            rf->towers_nb++;
    }
    fclose(file);
    return RETURN_SUCCESS;
}

static
int create_all_sprites(rf_t *rf)
{
    rf->planes = create_sprites(rf->planes_nb, "assets/img/plane.png",
        (sfVector2f){ 0.07125, 0.07125 });
    if (rf->planes == NULL)
        return RETURN_FAILURE;
    if (create_plane_hitboxes(rf->planes, rf->planes_nb) == RETURN_FAILURE)
        return RETURN_FAILURE;
    rf->towers = create_sprites(rf->towers_nb, "assets/img/tower.png",
        (sfVector2f){ 0.15, 0.15 });
    if (rf->towers == NULL)
        return RETURN_FAILURE;
    return RETURN_SUCCESS;
}

int parser(rf_t *rf, char *path)
{
    FILE *file = fopen(path, "r");
    char *buffer = NULL;
    size_t buff_size = 100;

    count_planes_towers(rf, file);
    if (!rf->planes_nb || !rf->towers_nb)
        return FAILURE_MSG("Invalid script file, towers/planes are required");
    if (create_all_sprites(rf) == RETURN_FAILURE)
        return RETURN_FAILURE;
    file = fopen(path, "r");
    if (!file)
        return FAILURE_MSG("Cannot open script file !");
    for (; getline(&buffer, &buff_size, file) != -1;) {
        MY_DEBUG("Script file: %s", buffer);
        if (*buffer == 'A' && parse_plane(rf, buffer) == RETURN_FAILURE)
            return FAILURE_MSG("Cannot parse plane !");
        if (*buffer == 'T' && parse_tower(rf, buffer) == RETURN_FAILURE)
            return FAILURE_MSG("Cannot parse tower !");
    }
    return (fclose(file), RETURN_SUCCESS);
}
