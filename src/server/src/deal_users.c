/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** deal_users
*/

#include "server.h"

bool user_exists(server_t *server, char *user_id)
{
    for (user_t *usr = server->users.tqh_first; usr != NULL;
    usr = usr->next_user.tqe_next) {
        if (strcmp(usr->uid, user_id) == 0)
            return true;
    }
    return false;
}

user_t *get_username(server_t *server, char *name)
{
    for (user_t *usr = server->users.tqh_first; usr != NULL;
    usr = usr->next_user.tqe_next) {
        if (strcmp(usr->name, name) == 0)
            return usr;
    }
    return NULL;
}

void ping_team_users(server_t *server, command_t *send, team_t *team)
{
    client_t *user;

    for (idd_t *tmp = team->users.tqh_first; tmp != NULL;
    tmp = tmp->next_id.tqe_next) {
        user = get_connected_user(server, tmp->uid);
        if (!user)
            continue;
        send_ping(&server->net, user->clid.fd, send);
    }
}
