/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** info_channel.c
*/

#include <stdio.h>
#include <unistd.h>
#include "server.h"

void info_channel(server_t *server, client_t *client, command_t *command)
{
    send_status_msg(&server->net, client->clid.fd, 210, "INFO_CHANNEL\n");
    dprintf(STDIN_FILENO, "INFO_CHANNEL\n");
}
