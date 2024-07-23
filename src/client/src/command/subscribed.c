/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** subscribed.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "client.h"
#include "utils.h"
#include "logging_client.h"

static int list_user(const unsigned int code, const char *team,
char **response)
{
    char **parse;

    if (code >= 400) {
        client_error_unknown_team(team);
        return code;
    }
    for (int i = 0; response[i] != NULL; ++i) {
        parse = parse_command(response[i], ",");
        client_print_users(parse[0], parse[1], atoi(parse[2]));
    }
    return code;
}

static int list_teams(const unsigned int code, char **response)
{
    char **parse;

    for (int i = 0; response[i] != NULL; ++i) {
        parse = parse_command(response[i], ",");
        client_print_teams(parse[0], parse[1], parse[2]);
    }
    return code;
}

static command_t check_args(char *args)
{
    command_t res = {0};

    if (!args) {
        res.code = -1;
        return res;
    }
    return format_message_to_server(DATA_TEAMS, args);
}

int subscribed(user_info_t *user, char *args)
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
    response = read_server(user->server.fd);
    if (response.code == -1)
        printf("Server not responding\n");
    return response.code;
}
