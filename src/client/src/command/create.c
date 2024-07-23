/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** create.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "client.h"
#include "utils.h"
#include "logging_client.h"

static command_t check_args(char *args, action_server_t action)
{
    command_t res = {0};

    if (!args) {
        res.code = -1;
        return res;
    }
    return format_message_to_server(action, args);
}

static void convert_context(user_info_t *user, action_server_t *action)
{
    switch (user->context) {
        case TEAM:
            *action = CREATE_TEAM;
            break;
        case CHANNEL:
            *action = CREATE_CHANNEL;
            break;
        case THREAD:
            *action = CREATE_THREAD;
            break;
        case REPLY:
            *action = CREATE_COMMENT;
            break;
    }
}

static void add_params(user_info_t *user, command_t *msg)
{
    switch (user->context) {
        case CHANNEL:
            strcat(msg->av[msg->ac], user->team_uuid);
            msg->ac++;
            break;
        case THREAD:
            strcat(msg->av[msg->ac], user->team_uuid);
            msg->ac++;
            strcat(msg->av[msg->ac], user->channel_uuid);
            msg->ac++;
            break;
        case REPLY:
            strcat(msg->av[msg->ac], user->team_uuid);
            msg->ac++;
            strcat(msg->av[msg->ac], user->channel_uuid);
            msg->ac++;
            strcat(msg->av[msg->ac], user->thread_uuid);
            msg->ac++;
            break;
    }
}

int create(user_info_t *user, char *args)
{
    action_server_t action = 0;
    command_t msg;
    response_t response = {0};
    char *to_add;

    convert_context(user, &action);
    if (!user->connected || action == 0) {
        client_error_unauthorized();
        return 0;
    }
    msg = check_args(args, action);
    if (msg.code == -1)
        return unknow_msg();
    add_params(user, &msg);
    send_message(&user->server, msg);
    return response.code;
}
