/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** info.c
*/

#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "utils.h"

static char *check_args(char *args)
{
    if (!args)
        return NULL;
    return parse_message_to_server(CREATE_TEAM, args);
}

int info(user_info_t *user, char *args)
{
    const char *msg = check_args(args);
    char **parse_res;
    unsigned int code;
    char *message;

    if (msg == NULL)
        return unknow_msg();
    return code;
}
