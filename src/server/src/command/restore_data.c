/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** restore_data.c
*/

#include <stdio.h>
#include <unistd.h>
#include "server.h"

void restore_data(server_t *server, client_t *client, command_t *command)
{
    send_status_msg(&server->net, client->clid.fd, 210, "RESTORE DATA\n");
    dprintf(STDIN_FILENO, "RESTORE DATA FROM FILES\n");
}
