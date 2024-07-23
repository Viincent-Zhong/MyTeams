/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** login.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "client.h"
#include "utils.h"
#include "logging_client.h"

static void free_elem(char **array)
{
    for (int i = 0; array[i]; ++i)
        free(array[i]);
    free(array);
}

static command_t check_args(user_info_t *user, char *args)
{
    command_t response = {0};

    if (!args) {
        response.code = -1;
        return response;
    }
    if (user->connected) {
        dprintf(STDIN_FILENO, "Already connect\n");
        response.code = -1;
        return response;
    }
    response = format_message_to_server(LOGIN_CLIENT, args);
    return response;
}

int login(user_info_t *user, char *args)
{
    command_t msg = check_args(user, args);
    response_t response = {0};
    char **res_av;

    if (msg.code == -1)
        return unknow_msg();
    send_message(&user->server, msg);
    response = read_server(user->server.fd);
    if (response.code == -1)
        printf("Server not responding\n");
    res_av = capture_args(response.response);
    if (response.code < 400) {
        strcpy(user->uid, res_av[0]);
        user->name = malloc(sizeof(char) * (strlen(res_av[1]) + 1));
        strcpy(user->name, res_av[1]);
        user->connected = true;
    } else
        printf("Can't login: %d %s\n", response.code, response.response);
    return response.code;
}
