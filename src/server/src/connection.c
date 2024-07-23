/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** connection
*/

#include <stdlib.h>
#include "server.h"
#include "logging_server.h"

void add_client(server_t *server, socket_t sock)
{
    client_t *tmp = malloc(sizeof(client_t));

    tmp->clid = sock;
    tmp->context = TEAM;
    tmp->user = NULL;
    TAILQ_INSERT_HEAD(&server->clid_head, tmp, next_client);
}

static void set_as_logout(server_t *serv, client_t *client)
{
    if (client->user && client->user->is_connected) {
        client->user->is_connected = false;
        server_event_user_logged_out(client->user->uid);
    }
}

void quit_dog(server_t *serv, client_t *client)
{
    set_as_logout(serv, client);
    close(client->clid.fd);
    TAILQ_REMOVE(&serv->clid_head, client, next_client);
    free(client);
}

void client_connection(server_t *server, socket_t *client, socket_t serv)
{
    client->addrlen = sizeof(client->addr);
    if ((client->fd = accept(serv.fd, (struct sockaddr *) &client->addr,
    (socklen_t *) &client->addrlen)) == -1)
        return;
    if (client->fd > server->net.max_fd)
        server->net.max_fd = client->fd;
    add_client(server, *client);
}
