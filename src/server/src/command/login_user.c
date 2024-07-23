/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** login_user.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "server.h"
#include "logging_server.h"

void create_user(server_t *server, client_t *client, const char *name)
{
    user_t *new_user = malloc(sizeof(user_t));
    char *res;

    generate_user(new_user, name);
    res = malloc(sizeof(char) * (strlen(name) + strlen(new_user->uid) + 6));
    client->user = new_user;
    TAILQ_INSERT_HEAD(&server->users, new_user, next_user);
    sprintf(res, "\"%s\" \"%s\"", client->user->uid, name);
    server_event_user_created(client->user->uid, name);
    server_event_user_logged_in(client->user->uid);
    send_status_msg(&server->net, client->clid.fd, 210, res);
    free(res);
}

void set_user(server_t *server, client_t *client, const char *name,
user_t *user)
{
    char *res;

    user->is_connected = true;
    server_event_user_logged_in(user->uid);
    client->user = user;
    res = malloc(sizeof(char) * (strlen(name) + strlen(user->uid) + 6));
    sprintf(res, "\"%s\" \"%s\"", client->user->uid, name);
    send_status_msg(&server->net, client->clid.fd, 210, res);
    free(res);
}

bool user_exist(server_t *server, client_t *client, const char *name)
{
    for (user_t *tmp = server->users.tqh_first; tmp != NULL;
    tmp = tmp->next_user.tqe_next) {
        if (strcmp(tmp->name, name) == 0 && tmp->is_connected)
            return false;
        if (strcmp(tmp->name, name) == 0 && !tmp->is_connected) {
            set_user(server, client, name, tmp);
            return true;
        }
    }
    create_user(server, client, name);
    return true;
}

bool error_handling(server_t *server, client_t *client, command_t *command)
{
    if (command->ac == 0) {
        send_status_msg(&server->net, client->clid.fd, 501,
        "Bad parameter for login\n");
        return false;
    }
    if (strlen(command->av[0]) > 32) {
        send_status_msg(&server->net, client->clid.fd, 501,
        "Bad name length (>32)\n");
        return false;
    }
    if (!user_exist(server, client, command->av[0])) {
        send_status_msg(&server->net, client->clid.fd, 420,
        "Can't login, user already connected\n");
        return false;
    }
    return true;
}

void login_user(server_t *server, client_t *client, command_t *command)
{
    command_t send = {0};
    user_t *user;

    if (!error_handling(server, client, command))
        return;
    send.ac = 2;
    send.code = 322;
    if (!(user = get_username(server, command->av[0])))
        return;
    strcpy(send.av[0], user->uid);
    strcpy(send.av[1], user->name);
    send_ping(&server->net, client->clid.fd, &send);
}
