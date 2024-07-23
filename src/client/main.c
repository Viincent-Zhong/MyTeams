/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** client main.c
*/

#include <stdio.h>
#include <string.h>
#include "client.h"

static int help(void)
{
    puts("USAGE: ./myteams_cli ip port");
    puts("\tip  is the server ip address on which the server socket listens");
    puts("\tport is the port number on which the server socket listens");
    return 0;
}

int main(int ac, char **av)
{
    if (ac < 2)
        return 84;
    if (ac == 2 && strcmp("-h", av[1]) == 0 ||
    strcmp("--help", av[1]) == 0)
        return help();
    if (client(ac - 1, av + 1) == -1)
        return 84;
    return 0;
}
