/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** create_channel.c
*/

#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "logging_server.h"

static void user_authorized(server_t *server, client_t *client, command_t
*command, command_t *send)
{
    if (!team_exist(server, command->av[2]) && send->code == 0) {
        send->code = 504;
        strcat(send->av[0], command->av[2]);
    }
    if (channel_exist(server, command->av[2], command->av[0])
    && send->code == 0)
        send->code = 430;
    if (!is_subscribed(server, command->av[2], client->user->uid)
    && send->code == 0)
        send->code = 502;
}

static bool error_handling(server_t *server, client_t *client, command_t
*command)
{
    command_t send = {0};

    if (command->ac != 3)
        send.code = 500;
    if (!client->user->is_connected && send.code == 0)
        send.code = 502;
    user_authorized(server, client, command, &send);
    if (send.code != 0) {
        send.ac = 1;
        send_ping(&server->net, client->clid.fd, &send);
        return false;
    }
    return true;
}

static bool channel_response(server_t *server, client_t *client,
command_t *command, char *uid)
{
    command_t send = {0};

    if (!uid) {
        send.code = 500;
        send_ping(&server->net, client->clid.fd, &send);
        return false;
    }
    send.ac = 3;
    send.code = 211;
    strcat(send.av[0], uid);
    strcat(send.av[1], command->av[1]);
    strcat(send.av[2], command->av[2]);
    send_ping(&server->net, client->clid.fd, &send);
    send.code = 324;
    ping_team_users(server, &send, get_team(server, command->av[2]));
    return true;
}

void create_channel(server_t *server, client_t *client, command_t *command)
{
    command_t send = {0};
    char *uid;

    if (!error_handling(server, client, command))
        return;
    uid = create_new_channel(server, command->av[0], command->av[1],
    command->av[2]);
    if (!channel_response(server, client, command, uid))
        return;
    server_event_channel_created(command->av[2], uid, command->av[0]);
}
