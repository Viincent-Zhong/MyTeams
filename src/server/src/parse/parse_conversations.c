/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** parse_conversations
*/

#include <stdlib.h>
#include "server.h"

static void add_message_list(struct message_list *msg, char *line)
{
    idd_t *tmp;
    char **ids = parse_string(line, "\a");

    if (!ids)
        return;
    TAILQ_INIT(msg);
    for (int i = 1; ids[i]; ++i) {
        tmp = create_id(ids[i]);
        TAILQ_INSERT_HEAD(msg, tmp, next_id);
    }
    free(ids);
}

static void add_parsed_conv(server_t *server, char *line)
{
    conversation_t *conv;
    char **parse = parse_string(line, "\b");
    int i = 0;

    if (!parse)
        return;
    for (; parse[i]; ++i);
    if (i == 2) {
        conv = malloc(sizeof(conversation_t));
        copy_id(conv->uid, parse[0]);
        add_message_list(&conv->messages, parse[1]);
        TAILQ_INSERT_HEAD(&server->convs, conv, next_conv);
    }
    free(parse);
}

void parse_conversation(server_t *server, char *path)
{
    char **lines = NULL;
    char *file = get_file_content(path);
    int len = 0;

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
        add_parsed_conv(server, lines[i]);
    }
    free(file);
    free(lines);
}
