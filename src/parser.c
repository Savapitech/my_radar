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
void parse_plane_buffer(rf_t *rf, char *buffer, size_t i)
{
    rf->planes[i].pos.x = (float)my_getnbr(buffer);
    buffer += baby_intlen((int)rf->planes[i].pos.x, 10) + 1;
    rf->planes[i].pos.y = (float)my_getnbr(buffer);
    buffer += baby_intlen((int)rf->planes[i].pos.x, 10) + 1;
    rf->planes[i].end_pos.x = (float)my_getnbr(buffer);
    buffer += baby_intlen((int)rf->planes[i].end_pos.x, 10) + 1;
    rf->planes[i].end_pos.y = (float)my_getnbr(buffer);
    buffer += baby_intlen((int)rf->planes[i].end_pos.y, 10) + 1;
    rf->planes[i].speed = my_getnbr(buffer);
    buffer += baby_intlen(rf->planes[i].speed, 10) + 1;
    rf->planes[i].time_to_take_off = my_getnbr(buffer);
    buffer += baby_intlen(rf->planes[i].time_to_take_off, 10) + 1;
}

static
int parse_plane(rf_t *rf, char *buffer)
{
    size_t i = rf->planes_i;

    buffer++;
    if (!isdigit(*buffer) && !isblank(*buffer))
        return RETURN_FAILURE;
    parse_plane_buffer(rf, buffer, i);
    MY_DEBUG("Plane #%01d start pos: %01d, %01d\n", i,
        (int)rf->planes[i].end_pos.x, (int)rf->planes[i].end_pos.y);
    rf->planes[i].rotation = atan2f(rf->planes[i].end_pos.y -
        rf->planes[i].pos.y, rf->planes[i].end_pos.x - rf->planes[i].pos.x);
    rf->planes_i++;
    return RETURN_SUCCESS;
}

static
int parse_tower(rf_t *rf, char *buffer)
{
    size_t i = rf->towers_i;

    buffer++;
    if (!isdigit(*buffer) && !isblank(*buffer))
        return RETURN_FAILURE;
    rf->towers[i].pos.x = (float)my_getnbr(buffer);
    buffer += baby_intlen((int)rf->towers[i].pos.x, 10) + 1;
    rf->towers[i].pos.y = (float)my_getnbr(buffer);
    buffer += baby_intlen((int)rf->towers[i].pos.y, 10) + 1;
    rf->towers[i].radius = (float)my_getnbr(buffer);
    buffer += baby_intlen(rf->towers[i].radius, 10) + 1;
    MY_DEBUG("Tower #%01d pos: %01d, %01d\n", i,
        (int)rf->towers[i].pos.x, (int)rf->towers[i].pos.y);
    rf->towers_i++;
    sfSprite_setPosition(rf->towers[i].sprite,
        (sfVector2f){ rf->towers[i].pos.x - 38.4,
        rf->towers[i].pos.y - 38.4 });
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
    rf->planes = create_sprites(rf->planes_nb, R_PLANE_TEXTURE_PATH,
        (sfVector2f){ 0.07125, 0.07125 });
    if (rf->planes == NULL)
        return RETURN_FAILURE;
    if (create_plane_hitboxes(rf->planes, rf->planes_nb) == RETURN_FAILURE)
        return RETURN_FAILURE;
    rf->towers = create_sprites(rf->towers_nb, R_TOWER_TEXTURE_PATH,
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
