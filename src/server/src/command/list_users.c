/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** list_users
*/

#include "server.h"

static bool error_handling(server_t *server, client_t *client)
{
    command_t send = {0};

    if (!client->user->is_connected) {
        send.code = 502;
        send_ping(&server->net, client->clid.fd, &send);
        return false;
    }
    return true;
}

void list_users(server_t *server, client_t *client, command_t *data)
{
    command_t send = {0};

    if (!error_handling(server, client))
        return;
    send.code = 202;
    send.ac = 3;
    for (user_t *usr = server->users.tqh_first; usr != NULL;
    usr = usr->next_user.tqe_next) {
        strcpy(send.av[0], usr->uid);
        strcpy(send.av[1], usr->name);
        if (user_is_connected(server, usr->uid))
            strcpy(send.av[2], "1");
        else
            strcpy(send.av[2], "0");
        send_ping(&server->net, client->clid.fd, &send);
    }
}
