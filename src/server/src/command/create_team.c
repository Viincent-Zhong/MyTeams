/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** create_team.c
*/

#include <stdio.h>
#include <unistd.h>
#include "logging_server.h"
#include "server.h"

void team_ping_all(server_t *serv, char *uid, char *name, char *description)
{
    command_t send = {0};

    send.code = 310;
    send.ac = 3;
    if (uid)
        strcat(send.av[0], uid);
    if (name)
        strcat(send.av[1], name);
    if (description)
        strcat(send.av[2], description);
    ping_all_user(serv, &send);
}

static bool error_handling(server_t *server, client_t *client,
command_t *command)
{
    command_t send = {0};

    if (command->ac != 2)
        send.code = 500;
    if (!client->user->is_connected && send.code == 0)
        send.code = 502;
    if (team_exist(server, command->av[0]) && send.code == 0)
        send.code = 430;
    if (send.code != 0) {
        send_ping(&server->net, client->clid.fd, &send);
        return false;
    }
    return true;
}

void create_team(server_t *server, client_t *client, command_t *command)
{
    command_t send = {0};
    char *uid;

    if (!error_handling(server, client, command))
        return;
    uid = create_new_team(server, command->av[0], command->av[1],
    client->user->uid);
    send.code = 311;
    send.ac = 3;
    strcat(send.av[0], uid);
    strcat(send.av[1], command->av[0]);
    strcat(send.av[2], command->av[1]);
    send_ping(&server->net, client->clid.fd, &send);
    server_event_team_created(uid, command->av[0], client->user->uid);
    team_ping_all(server, uid, command->av[0], command->av[1]);
}
