/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** init.c
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

static bool check_params(int ac, char **av)
{
    if (ac != 2)
        return false;
    for (int i = 0; av[0][i] != '\0'; ++i)
        if (av[0][i] != '.' && av[0][i] < '0' || av[0][i] > '9') {
            printf("%c\n", av[0][i]);
            return false;
        }
    for (int i = 0; av[1][i] != '\0'; ++i)
        if (av[1][i] < '0' || av[1][i] > '9')
                return false;
    return true;
}

static int connect_server(const char *ip, const unsigned int port)
{
    int sock = 0;
    struct sockaddr_in addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Error socket\n");
        return -1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &addr.sin_addr) <= 0) {
        printf("Error address\n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        printf("Error connection\n");
        return -1;
    }
    return sock;
}

static void init_user(user_info_t *user)
{
    user->id = 0;
    user->name = NULL;
    user->connected = false;
    memset(user->team_uuid, 0, UUID_STR_LEN);
    memset(user->channel_uuid, 0, UUID_STR_LEN);
    memset(user->thread_uuid, 0, UUID_STR_LEN);
    user->server.fd = 0;
    user->context = TEAM;
    user->server.timeout.tv_sec = 10;
    user->server.timeout.tv_usec = 0;
}

int init_client(int ac, char **av, user_info_t *user)
{
    if (!check_params(ac, av))
        return -1;
    init_user(user);
    user->server.fd = connect_server(av[0], atoi(av[1]));
    if (user->server.fd == -1)
        return -1;
    return 0;
}
