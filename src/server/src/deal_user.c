/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** deal_user
*/

#include "server.h"

void generate_user(user_t *user, const char *name)
{
    TAILQ_INIT(&user->teams);
    TAILQ_INIT(&user->convs);
    user->is_connected = true;
    user->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(user->name, name);
    generate_uuid(user->uid);
}

void ping_all_user(server_t *serv, command_t *send)
{
    for (client_t *client = TAILQ_FIRST(&serv->clid_head), *tmp;
    client != NULL; client = tmp) {
        send_ping(&serv->net, client->clid.fd, send);
        tmp = TAILQ_NEXT(client, next_client);
    }
}

user_t *get_user(server_t *serv, char *user_id)
{
    for (user_t *team = serv->users.tqh_first; team != NULL;
    team = team->next_user.tqe_next) {
        if (strcmp(team->uid, user_id) == 0)
            return team;
    }
    return NULL;
}

client_t *get_connected_user(server_t *serv, char *user_id)
{
    for (client_t *cli = serv->clid_head.tqh_first; cli != NULL;
    cli = cli->next_client.tqe_next) {
        if (strcmp(cli->user->uid, user_id) == 0)
            return cli;
    }
    return NULL;
}

bool user_is_connected(server_t *serv, char *user_id)
{
    for (client_t *cli = serv->clid_head.tqh_first; cli != NULL;
    cli = cli->next_client.tqe_next) {
        if (strcmp(cli->user->uid, user_id) == 0 && cli->user &&
        cli->user->is_connected)
            return true;
    }
    return false;
}
