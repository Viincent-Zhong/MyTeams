/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** leaving_team.c
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

static void remove_from_team(team_t *team, char *user_id)
{
    for (idd_t *id = team->users.tqh_first; id != NULL;
    id = id->next_id.tqe_next) {
        if (strcmp(id->uid, user_id) == 0) {
            TAILQ_REMOVE(&team->users, id, next_id);
            free(id);
            break;
        }
    }
}

void leaving_team(server_t *server, client_t *client, command_t *command)
{
    command_t send = {0};
    team_t *team;
    idd_t *id;

    if (!(team = error_handling(server, client, command)))
        return;
    id = create_id(client->user->uid);
    remove_from_team(team, client->user->uid);
    server_event_user_unsubscribed(team->uid, client->user->uid);
    send.ac = 2;
    send.code = 204;
    strcat(send.av[0], client->user->uid);
    strcat(send.av[1], team->uid);
    send_ping(&server->net, client->clid.fd, &send);
}
