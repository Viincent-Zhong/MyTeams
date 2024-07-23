/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** socket
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"
#include <uuid/uuid.h>

static unsigned int norm_init_socket(socket_t *sock)
{
    if (bind(sock->fd, (struct sockaddr *) &sock->addr,
    sizeof(sock->addr)) == -1) {
        perror("Bind");
        return -1;
    }
    if (listen(sock->fd, SOMAXCONN) == -1) {
        perror("Listen");
        return -1;
    }
    return 0;
}

int init_socket(socket_t *sock, int port)
{
    if ((sock->fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket");
        return -1;
    }
    if (setsockopt(sock->fd, SOL_SOCKET, SO_REUSEADDR, &(int){1},
    sizeof(int)) < 0) {
        perror("setsockopt");
        return -1;
    }
    sock->addrlen = sizeof(sock->addr);
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = INADDR_ANY;
    sock->addr.sin_port = htons(port);
    return norm_init_socket(sock);
}

void send_message(serv_info_t *serv, const command_t message)
{
    FD_ZERO(&serv->wdfs);
    FD_SET(serv->fd, &serv->wdfs);
    if (select(serv->fd + 1, NULL, &serv->wdfs, NULL, NULL) == -1)
        return;
    if (FD_ISSET(serv->fd, &serv->wdfs)) {
        if (write(serv->fd, &message, sizeof(command_t)) == -1)
            puts("Error can't send message to the server");
    } else
        puts("Error can't send message to the server");
}

void generate_uuid(char *uid)
{
    uuid_t dog;

    uuid_generate_random(dog);
    uuid_unparse(dog, uid);
}
