/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** parse_users
*/

#include <stdlib.h>
#include "server.h"

static void add_conv_list(struct conv_list *convs, char *line)
{
    idd_t *tmp;
    char **ids = parse_string(line, "\a");

    if (!ids)
        return;
    TAILQ_INIT(convs);
    for (int i = 1; ids[i]; ++i) {
        tmp = create_id(ids[i]);
        TAILQ_INSERT_HEAD(convs, tmp, next_id);
    }
    free(ids);
}

static void add_team_list(struct team_list *teams, char *line)
{
    idd_t *tmp;
    char **ids = parse_string(line, "\a");

    if (!ids)
        return;
    TAILQ_INIT(teams);
    for (int i = 1; ids[i]; ++i) {
        tmp = create_id(ids[i]);
        TAILQ_INSERT_HEAD(teams, tmp, next_id);
    }
    free(ids);
}

static void add_parsed_user(server_t *serv, char *line)
{
    user_t *usr;
    char **parse = parse_string(line, "\b");
    int i = 0;

    if (!parse)
        return;
    for (;parse[i]; ++i);
    if (i == 4) {
        usr = malloc(sizeof(user_t));
        usr->is_connected = false;
        copy_id(usr->uid, parse[0]);
        usr->name = malloc(sizeof(char) * (strlen(parse[1]) + 1));
        strcpy(usr->name, parse[1]);
        add_team_list(&usr->teams, parse[2]);
        add_conv_list(&usr->convs, parse[3]);
        TAILQ_INSERT_HEAD(&serv->users, usr, next_user);
    }
    free(parse);
}

void parse_user(server_t *server, char *path)
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
        add_parsed_user(server, lines[i]);
    }
    free(file);
    free(lines);
}
