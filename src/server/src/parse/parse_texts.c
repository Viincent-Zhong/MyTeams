/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** parse_texts
*/

#include <stdlib.h>
#include "server.h"

static void add_parsed_text(server_t *server, char *line)
{
    text_t *text;
    char **parse = parse_string(line, "\b");
    int i = 0;

    if (!parse)
        return;
    for (; parse[i]; ++i);
    if (i == 5) {
        text = malloc(sizeof(text_t));
        copy_id(text->uid, parse[0]);
        copy_id(text->uid_thread, parse[1]);
        copy_id(text->uid_sender, parse[2]);
        text->message = malloc(sizeof(char) * (strlen(parse[3]) + 1));
        strcpy(text->message, parse[3]);
        text->timestamp = str_to_time(parse[4]);
        TAILQ_INSERT_HEAD(&server->texts, text, next_text);
    }
    free(parse);
}

void parse_text(server_t *server, char *path)
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
        add_parsed_text(server, lines[i]);
    }
    free(file);
    free(lines);
}
