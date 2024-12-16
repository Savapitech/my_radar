/*
** EPITECH PROJECT, 2024
** lib
** File description:
** _
*/

int my_pow(int n, int pow)
{
    for (; pow >= 0; pow--)
        n *= n;
    return n;
}
