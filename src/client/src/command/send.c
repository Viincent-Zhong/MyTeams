/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** send.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "client.h"
#include "logging_client.h"
#include "utils.h"

static command_t check_args(char *args)
{
    command_t res = {0};

    if (!args) {
        res.code = -1;
        return res;
    }
    return format_message_to_server(SAVE_CONVERSATION, args);
}

int send_fct(user_info_t *user, char *args)
{
    command_t msg = check_args(args);
    response_t response = {0};

    if (msg.code == -1)
        return unknow_msg();
    if (!user->connected) {
        client_error_unauthorized();
        return 0;
    }
    send_message(&user->server, msg);
    return response.code;
}
