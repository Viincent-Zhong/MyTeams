/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** joining_team.c
*/

#include <stdio.h>
#include <unistd.h>
#include "logging_server.h"
#include "server.h"

static team_t *error_handling(server_t *server, client_t *client,
command_t *command)
{
    team_t *team;
    command_t send = {0};

    if (command->ac != 1)
        send.code = 500;
    if (!client->user->is_connected && send.code == 0)
        send.code = 502;
    if (!(team = get_team(server, command->av[0])) && send.code == 0) {
        send.code = 504;
        strcat(send.av[0], command->av[0]);
    }
    if (send.code != 0) {
        send.ac = 1;
        send_ping(&server->net, client->clid.fd, &send);
        return NULL;
    }
    return team;
}

void joining_team(server_t *server, client_t *client, command_t *command)
{
    command_t send = {0};
    team_t *team;
    idd_t *id;

    if (!(team = error_handling(server, client, command)))
        return;
    id = create_id(client->user->uid);
    TAILQ_INSERT_HEAD(&team->users, id, next_id);
    server_event_user_subscribed(team->uid, client->user->uid);
    send.ac = 2;
    send.code = 203;
    strcat(send.av[0], client->user->uid);
    strcat(send.av[1], team->uid);
    send_ping(&server->net, client->clid.fd, &send);
}
