/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** server.c
*/

#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include "server.h"
#include "utils.h"
#include "logging_server.h"

static volatile sig_atomic_t alive = 1;

static bool handle_params(int ac, char **av)
{
    if (ac != 1)
        return false;
    for (int i = 0; av[0][i] != '\0'; ++i)
        if (av[0][i] < '0' || av[0][i] > '9')
            return false;
    return true;
}

static void sig_handler(int _)
{
    (void)_;
    alive = 0;
}

static int data_to_file(server_t *serv)
{
    if (alive)
        return -1;

    save_all(serv);
    free_server(serv);
    return 0;
}

static int init_server(int ac, char **av, server_t *serv)
{
    if (!handle_params(ac, av))
        return -1;
    if (init_socket(&serv->serv, atoi(av[0])) == -1)
        return -1;
    TAILQ_INIT(&serv->clid_head);
    parse_all(serv);
    serv->net.max_fd = serv->serv.fd;
    signal(SIGINT, sig_handler);
}

int server(int ac, char **av)
{
    server_t serv;
    socket_t client;

    if (init_server(ac, av, &serv) == -1)
        return -1;
    for (user_t *tmp = serv.users.tqh_first; tmp != NULL;
    tmp = tmp->next_user.tqe_next)
        server_event_user_loaded(tmp->uid, tmp->name);
    while (alive) {
        if (select_whole_server(&serv) == -1)
            return data_to_file(&serv);
        if (FD_ISSET(serv.serv.fd, &serv.net.rdfs))
            client_connection(&serv, &client, serv.serv);
        else
            detect_clients(&serv);
    }
    return data_to_file(&serv);
}
