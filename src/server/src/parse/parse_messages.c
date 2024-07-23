/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** parse_messages
*/

#include <stdlib.h>
#include "server.h"

time_t str_to_time(const char *str)
{
    char *error;
    time_t timestamp;

    return strtol(str, &error, 10);
}

static void add_parsed_message(server_t *server, char *line)
{
    message_t *msg;
    char **parse = parse_string(line, "\b");
    int i = 0;

    if (!parse)
        return;
    for (; parse[i]; ++i);
    if (i == 5) {
        msg = malloc(sizeof(message_t));
        copy_id(msg->uid, parse[0]);
        copy_id(msg->uid_send, parse[1]);
        copy_id(msg->uid_receive, parse[2]);
        msg->message = malloc(sizeof(char) * (strlen(parse[3]) + 1));
        strcpy(msg->message, parse[3]);
        msg->timestamp = str_to_time(parse[4]);
        TAILQ_INSERT_HEAD(&server->messages, msg, next_message);
    }
    free(parse);
}

void parse_message(server_t *server, char *path)
{
    char **lines = NULL;
    char *file = get_file_content(path);

    if (file == NULL)
        return;
    lines = parse_string(file, "\n");
    if (lines == NULL) {
        free(file);
        return;
    }
    for (int i = 0; lines[i]; ++i) {
        if (i == 0)
            continue;
        add_parsed_message(server, lines[i]);
    }
    free(file);
    free(lines);
}
