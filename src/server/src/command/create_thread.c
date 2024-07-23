/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** create_thread.c
*/

#include <stdio.h>
#include <unistd.h>
#include "server.h"
#include "logging_server.h"

static bool valid_thread(server_t *server, command_t *command, command_t *send,
client_t *client)
{
    if (!team_exist(server, command->av[2]) && send->code == 0) {
        send->code = 504;
        strcat(send->av[0], command->av[2]);
    }
    if (!is_subscribed(server, command->av[2], client->user->uid)
    && send->code == 0)
        send->code = 502;
    if (!channel_in_team(server, command->av[2], command->av[3])
    && send->code == 0) {
        strcat(send->av[0], command->av[3]);
        send->code = 505;
    }
    if (thread_exist(server, command->av[0], command->av[3])
    && send->code == 0)
        send->code = 430;
}

static bool error_handling(server_t *server, client_t *client,
command_t *command)
{
    command_t send = {0};

    if (command->ac != 4)
        send.code = 500;
    if (!client->user->is_connected && send.code == 0)
        send.code = 450;
    valid_thread(server, command, &send, client);
    if (send.code != 0) {
        send.ac = 1;
        send_ping(&server->net, client->clid.fd, &send);
        return false;
    }
    return true;
}

static void ping_user_thread_created(server_t *server, client_t *client,
thread_t *thr, command_t *send)
{
    server_event_thread_created(thr->uid_channel, thr->uid,
    client->user->uid, thr->title, thr->body);
    send->ac = 5;
    strcat(send->av[0], thr->uid);
    strcat(send->av[1], thr->uid_user);
    sprintf(send->av[2], "%ld", thr->timestamp);
    strcat(send->av[3], thr->title);
    strcat(send->av[4], thr->body);
    send->code = 212;
    send_ping(&server->net, client->clid.fd, send);
    send->code = 325;
    ping_team_users(server, send, get_team(server,
    get_channel(server, thr->uid_channel)->uid_team));
}

void create_thread(server_t *server, client_t *client, command_t *command)
{
    command_t send = {0};
    thread_t *thr;
    char **params = malloc(sizeof(char *) * (5));

    if (!error_handling(server, client, command))
        return;
    params[0] = command->av[3];
    params[1] = command->av[0];
    params[2] = command->av[1];
    params[3] = client->user->uid;
    params[4] = NULL;
    if (!(thr = create_new_thread(server, params))) {
        send.code = 430;
        send_ping(&server->net, client->clid.fd, &send);
        return;
    }
    free(params);
    ping_user_thread_created(server, client, thr, &send);
}
