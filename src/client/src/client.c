/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** client.c
*/

#include <stdio.h>
#include "client.h"

static int select_client(serv_info_t *serv)
{
    FD_ZERO(&serv->rdfs);
    FD_ZERO(&serv->wdfs);
    FD_SET(serv->fd, &serv->rdfs);
    FD_SET(0, &serv->rdfs);
    if (select(serv->fd + 1, &serv->rdfs, &serv->wdfs, NULL, NULL) == -1)
        return -1;
}

static int server_announcement(user_info_t *user)
{
    command_t response = read_client(user->server.fd);

    if (response.code == -1) {
        printf("Server closed\n");
        return -1;
    }
    decrypt_announce(&response, user);
    return 0;
}

int client(int ac, char **av)
{
    user_info_t user = {0};
    int res = 0;

    if (init_client(ac, av, &user) == -1)
        return -1;
    while (1) {
        if (select_client(&user.server) == -1)
            return -1;
        if ((res = get_command(&user)) != 1)
            return res;
        if (FD_ISSET(user.server.fd, &user.server.rdfs) &&
        server_announcement(&user) == -1)
            return -1;
    }
    return 0;
}
