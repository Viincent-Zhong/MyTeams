/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** logout.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "client.h"
#include "utils.h"
#include "logging_client.h"

void free_elem(char *msg, char **parse_res, char *response)
{
    free(msg);
    free(parse_res);
    free(response);
}

int logout(user_info_t *user, char *args)
{
    command_t msg = {0};
    response_t response = {0};

    msg.code = LOGOUT_CLIENT;
    if (!user->connected) {
        client_error_unauthorized();
        return 0;
    }
    send_message(&user->server, msg);
    response = read_server(user->server.fd);
    if (response.code == -1)
        printf("Server not responding\n");
    if (response.code != 210)
        return response.code;
    free(user->name);
    memset(user->uid, 0, UUID_STR_LEN);
    user->connected = false;
    return response.code;
}
