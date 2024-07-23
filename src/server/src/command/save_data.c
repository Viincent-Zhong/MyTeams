/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** save_data.c
*/

#include <stdio.h>
#include <unistd.h>
#include "server.h"

void save_data(server_t *server, client_t *client, command_t *command)
{
    send_status_msg(&server->net, client->clid.fd, 210, "SAVE DATA\n");
    dprintf(STDIN_FILENO, "SAVE ALL DATA IN FILES\n");
}
