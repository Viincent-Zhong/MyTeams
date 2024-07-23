/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** handle_client
*/

#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include "server.h"

void send_status_msg(net_t *serv, int fd, int status, char *msg)
{
    response_t response = {0};

    FD_ZERO(&serv->wdfs);
    FD_SET(fd, &serv->wdfs);
    if (select(serv->max_fd + 1, &serv->rdfs,
        &serv->wdfs, &serv->edfs, NULL) == -1)
        return;
    if (!FD_ISSET(fd, &serv->wdfs))
        return;
    if (fcntl(fd, F_GETFD) == -1 || errno == EBADF)
        return;
    response.code = status;
    strcat(response.response, msg);
    write(fd, &response, sizeof(response_t));
}

int client_message(server_t *serv, client_t *client)
{
    command_t res = read_client(client->clid.fd);

    if (res.code == -1)
        return -1;
    exec_command(serv, client, &res);
    return 0;
}

int detect_clients(server_t *serv)
{
    for (client_t *client = TAILQ_FIRST(&serv->clid_head), *tmp;
    client != NULL; client = tmp) {
        tmp = TAILQ_NEXT(client, next_client);
        if (client->clid.fd != -1 && FD_ISSET(client->clid.fd, &serv->net.rdfs)
        && client_message(serv, client) == -1)
            quit_dog(serv, client);
    }
}

void send_ping(net_t *serv, int fd, command_t *send)
{
    FD_ZERO(&serv->wdfs);
    FD_SET(fd, &serv->wdfs);
    if (select(serv->max_fd + 1, &serv->rdfs,
        &serv->wdfs, &serv->edfs, NULL) == -1)
        return;
    if (!FD_ISSET(fd, &serv->wdfs))
        return;
    if (fcntl(fd, F_GETFD) == -1 || errno == EBADF)
        return;
    write(fd, send, sizeof(command_t));
}
