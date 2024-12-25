/*
** EPITECH PROJECT, 2024
** __
** File description:
** _
*/

#include "lib.h"
#include "radar.h"

static
void printf_usages(void)
{
    my_printf("Air traffic simulation panel\n"
        "USAGE\n"
        "  ./my_radar [OPTIONS] path_to_script\n"
        "  path_to_script The path to the script file.\n"
        "OPTIONS\n"
        "  -h print the usage and quit.\n"
        "USER INTERACTIONS\n"
        "  `L' key enable/disable hitboxes and areas.\n"
        "  `S' key enable/disable sprites.\n");
}

int main(int argc, char **argv)
{
    if (argc < 2)
        return (my_puterr("./my_radar: bad arguments: 0 given but 84 is"
            "required retry with -h\n"), RETURN_FAILURE);
    if (my_strcmp(argv[1], "-h") == 0)
        return (printf_usages(), RETURN_SUCCESS);
    MY_DEBUG_MSG("Debug mode activated");
    return radar(argv);
}
