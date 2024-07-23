/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** info_thread.c
*/

#include <stdio.h>
#include <unistd.h>
#include "server.h"

void info_thread(server_t *server, client_t *client, command_t *command)
{
    send_status_msg(&server->net, client->clid.fd, 210, "INFO THREAD\n");
    dprintf(STDIN_FILENO, "INFO THREAD\n");
}
