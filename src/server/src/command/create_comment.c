/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** create_comment.c
*/

#include <stdio.h>
#include <unistd.h>
#include "logging_server.h"
#include "server.h"

static bool valid_thread(server_t *server, command_t *command, command_t *send,
client_t *client)
{
    if (!team_exist(server, command->av[1]) && send->code == 0) {
        send->code = 504;
        strcat(send->av[0], command->av[1]);
    }
    if (!is_subscribed(server, command->av[1], client->user->uid)
    && send->code == 0)
        send->code = 502;
    if (!channel_in_team(server, command->av[1], command->av[2])
    && send->code == 0) {
        strcat(send->av[0], command->av[2]);
        send->code = 505;
    }
    if (!thread_in_channel(server, command->av[2], command->av[3])
    && send->code == 0) {
        strcat(send->av[0], command->av[3]);
        send->code = 506;
    }
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

static void ping_reply_sender(server_t *server, text_t *txt, client_t *client,
command_t *send)
{
    send->code = 213;
    send->ac = 4;
    strcpy(send->av[0], txt->uid_thread);
    strcpy(send->av[1], client->user->uid);
    sprintf(send->av[2], "%ld", txt->timestamp);
    strcpy(send->av[3], txt->message);
}

static void ping_thread_owner(server_t *server, text_t *txt, command_t *send,
client_t *client)
{
    thread_t *thread = get_thread(server, txt->uid_thread);
    channel_t *ch;
    team_t *team;
    client_t *user;

    if (!thread || !(user = get_connected_user(server, thread->uid_user)))
        return;
    if (!(ch = get_channel(server, thread->uid_channel)) ||
    !(team = get_team(server, ch->uid_team)))
        return;
    send->code = 313;
    send->ac = 4;
    strcpy(send->av[0], team->uid);
    strcpy(send->av[1], thread->uid);
    strcpy(send->av[2], client->user->uid);
    strcpy(send->av[3], txt->message);
    ping_team_users(server, send, team);
}

void create_comment(server_t *server, client_t *client, command_t *command)
{
    return;
}
