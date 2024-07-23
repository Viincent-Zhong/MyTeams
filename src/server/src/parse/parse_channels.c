/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** parse_channels
*/

#include <stdlib.h>
#include <string.h>
#include "server.h"

static void add_thread_list(struct thread_list *thr, char *line)
{
    idd_t *tmp;
    char **ids = parse_string(line, "\a");

    if (!ids)
        return;
    TAILQ_INIT(thr);
    for (int i = 1; ids[i]; ++i) {
        tmp = create_id(ids[i]);
        TAILQ_INSERT_HEAD(thr, tmp, next_id);
    }
    free(ids);
}

static void add_parsed_channel(server_t *server, char *line)
{
    channel_t *channel;
    char **parse = parse_string(line, "\b");
    int i = 0;

    if (!parse)
        return;
    for (; parse[i]; ++i);
    if (i == 5) {
        channel = malloc(sizeof(channel_t));
        copy_id(channel->uid, parse[0]);
        channel->name = malloc(sizeof(char) * (strlen(parse[1]) + 1));
        strcpy(channel->name, parse[1]);
        channel->description = malloc(sizeof(char) * (strlen(parse[2]) + 1));
        strcpy(channel->description, parse[2]);
        copy_id(channel->uid_team, parse[3]);
        add_thread_list(&channel->threads, parse[4]);
        TAILQ_INSERT_HEAD(&server->channels, channel, next_channel);
    }
    free(parse);
}

void parse_channel(server_t *server, char *path)
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
        add_parsed_channel(server, lines[i]);
    }
    free(file);
    free(lines);
}
