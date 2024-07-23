/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** user.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "utils.h"
#include "logging_client.h"

static command_t check_args(char *args)
{
    command_t res = {0};

    if (!args) {
        res.code = -1;
        return res;
    }
    return format_message_to_server(DATA_USERS, args);
}

int user_fct(user_info_t *user, char *args)
{
    command_t msg = check_args(args);
    response_t response = {0};

    if (!user->connected) {
        client_error_unauthorized();
        return 0;
    }
    if (msg.code == -1)
        return unknow_msg();
    send_message(&user->server, msg);
    return response.code;
}
