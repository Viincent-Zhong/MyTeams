/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** server main.c
*/

#include <stdio.h>
#include "server.h"

static int help(void)
{
    puts("USAGE: ./myteams_server port");
    puts("\n\tport is the port number on which the server socket listens.");
    return 0;
}

int main(int ac, char **av)
{
    if (ac != 2)
        return 84;
    if (ac == 2 && strcmp("-h", av[1]) == 0 ||
    strcmp("--help", av[1]) == 0)
        return help();
    if (server(ac - 1, av + 1) == -1) {
        printf("eheheheh\n");
        return 84;
    }
    return 0;
}
