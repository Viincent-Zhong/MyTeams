/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** use.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "client.h"
#include "utils.h"
#include "logging_client.h"
#include <uuid/uuid.h>

static bool error_handling(command_t message)
{
    for (int i = 0, limit = message.ac; i < limit; ++i)
        if (strlen(message.av[i]) > UUID_STR_LEN) {
            client_error_unauthorized();
            return false;
        }
    if (message.ac > 4) {
        printf("Bad number of parameter\n");
        return false;
    }
    return true;
}

static void norm_use(command_t *msg, user_info_t *user)
{
    switch (msg->ac) {
        case 0:
            user->context = TEAM;
            break;
        case 1:
            user->context = CHANNEL;
            strcpy(user->team_uuid, msg->av[0]);
            break;
        case 2:
            user->context = THREAD;
            strcpy(user->team_uuid, msg->av[0]);
            strcpy(user->channel_uuid, msg->av[1]);
            break;
        case 3:
            user->context = REPLY;
            strcpy(user->team_uuid, msg->av[0]);
            strcpy(user->channel_uuid, msg->av[1]);
            strcpy(user->thread_uuid, msg->av[2]);
            break;
    }
}

int use(user_info_t *user, char *args)
{
    command_t msg = format_message_to_server(CREATE_TEAM, args);

    if (!user->connected) {
        client_error_unauthorized();
        return 0;
    }
    if (!error_handling(msg))
        return 0;
    norm_use(&msg, user);
    return 0;
}
