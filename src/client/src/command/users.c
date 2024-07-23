/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** users.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "logging_client.h"
#include "utils.h"

static command_t check_args(char *args)
{
    command_t res = {0};

    res.code = LIST_USER;
    return res;
}

int users(user_info_t *user, char *args)
{
    command_t msg = check_args(args);
    response_t response = {0};

    if (!user->connected) {
        client_error_unauthorized();
        return 0;
    }
    send_message(&user->server, msg);
    return response.code;
}
