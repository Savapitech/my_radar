/*
** EPITECH PROJECT, 2024
** CPoolDay08
** File description:
** ./my_realloc.c
*/

#include "lib.h"

void *my_realloc(void *ptr, size_t actual_size, size_t new_size)
{
    void *new;

    if (ptr == NULL)
        return ptr;
    if (!actual_size && !new_size)
        return NULL;
    new = malloc(new_size);
    if (new == NULL)
        return NULL;
    my_memcpy(new, ptr, actual_size);
    return (free(ptr), new);
}
