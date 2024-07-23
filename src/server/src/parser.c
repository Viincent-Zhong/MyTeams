/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** parser
*/

#include <stdlib.h>
#include "server.h"

void copy_id(char *uid, char *copy)
{
    int len = 0;

    memcpy(uid, copy, (len = strlen(copy)) ? len :
    (len = UUID_STR_LEN - 1));
    uid[len] = '\0';
}

idd_t *create_id(char *uid)
{
    idd_t *new_id = malloc(sizeof(idd_t));

    copy_id(new_id->uid, uid);
    return new_id;
}

static int init_parse(server_t *server)
{
    TAILQ_INIT(&server->texts);
    TAILQ_INIT(&server->threads);
    TAILQ_INIT(&server->channels);
    TAILQ_INIT(&server->teams);
    TAILQ_INIT(&server->users);
    TAILQ_INIT(&server->messages);
    TAILQ_INIT(&server->convs);
}

int parse_all(server_t *server)
{
    init_parse(server);
    parse_channel(server, CHANNEL_PATH);
    parse_conversation(server, CONV_PATH);
    parse_message(server, MESSAGE_PATH);
    parse_team(server, TEAM_PATH);
    parse_text(server, TEXT_PATH);
    parse_thread(server, THREAD_PATH);
    parse_user(server, USER_PATH);
    return 0;
}
