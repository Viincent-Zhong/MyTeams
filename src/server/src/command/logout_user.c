/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** logout_user.c
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "logging_server.h"

void logout_user(server_t *server, client_t *client, command_t *command)
{
    command_t send = {0};
    user_t *user;

    if (client->user && client->user->is_connected) {
        client->user->is_connected = false;
        server_event_user_logged_out(client->user->uid);
        send_status_msg(&server->net, client->clid.fd, 210, "");
        if (!(user = get_user(server, client->user->uid)))
            return;
        send.ac = 2;
        send.code = 323;
        strcpy(send.av[0], user->uid);
        strcpy(send.av[1], user->name);
        ping_all_user(server, &send);
    } else
        send_status_msg(&server->net, client->clid.fd, 501, "LOGOUT USER\n");
}
