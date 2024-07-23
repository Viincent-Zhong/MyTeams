/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** info_team.c
*/

#include <stdio.h>
#include <unistd.h>
#include "server.h"

void info_team(server_t *server, client_t *client, command_t *command)
{
    if (command->ac == 0) {
        send_status_msg(&server->net, client->clid.fd, 210,
        "1A1,Epitech,-4°|2A2,Pharaon,ahah\n");
    } else {
        send_status_msg(&server->net, client->clid.fd, 210,
        "1A1,pad,1|2A2,zozo,0\n");
    }
    dprintf(STDIN_FILENO, "INFO TEAM\n");
}
