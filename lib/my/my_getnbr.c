/*
** EPITECH PROJECT, 2024
** B-CPE-100-REN-1-1-cpoolday03-savinien.petitjean
** File description:
** my_getnbr.c
*/

#include <limits.h>

int my_getnbr(char const *str)
{
    unsigned long long result = 0;
    int i = 0;

    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
        str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
        i++;
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        if (result > INT_MAX)
            return INT_MAX;
        i++;
    }
    return (int)result;
}
