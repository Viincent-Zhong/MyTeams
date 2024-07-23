/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** subscribe.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
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
    return format_message_to_server(JOINING_TEAM, args);
}

int subscribe(user_info_t *user, char *args)
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
