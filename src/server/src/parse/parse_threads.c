/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** parse_threads
*/

#include <stdlib.h>
#include "server.h"

static void add_text_list(struct text_list *txt, char *line)
{
    idd_t *tmp;
    char **ids = parse_string(line, "\a");

    if (!ids)
        return;
    TAILQ_INIT(txt);
    for (int i = 1; ids[i]; ++i) {
        tmp = create_id(ids[i]);
        TAILQ_INSERT_HEAD(txt, tmp, next_id);
    }
    free(ids);
}

static void init_thread(thread_t *thread, char **parse)
{
    copy_id(thread->uid, parse[0]);
    copy_id(thread->uid_channel, parse[1]);
    add_text_list(&thread->texts, parse[2]);
    thread->title = malloc(sizeof(char) * (strlen(parse[3]) + 1));
    strcpy(thread->title, parse[3]);
    thread->body = malloc(sizeof(char) * (strlen(parse[4]) + 1));
    strcpy(thread->body, parse[4]);
    thread->timestamp = str_to_time(parse[5]);
    copy_id(thread->uid_user, parse[6]);
}

static void add_parsed_thread(server_t *server, char *line)
{
    thread_t *thread;
    char **parse = parse_string(line, "\b");
    int i = 0;

    if (!parse)
        return;
    for (; parse[i]; ++i);
    if (i == 7) {
        thread = malloc(sizeof(thread_t));
        init_thread(thread, parse);
        TAILQ_INSERT_HEAD(&server->threads, thread, next_thread);
    }
    free(parse);
}

void parse_thread(server_t *server, char *path)
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
        add_parsed_thread(server, lines[i]);
    }
    free(file);
    free(lines);
}
