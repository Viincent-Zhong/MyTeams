/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** parse_teams
*/

#include <stdlib.h>
#include "server.h"

static void add_channel_list(struct channel_list *chans, char *line)
{
    idd_t *tmp;
    char **ids = parse_string(line, "\a");

    if (!ids)
        return;
    TAILQ_INIT(chans);
    for (int i = 1; ids[i]; ++i) {
        tmp = create_id(ids[i]);
        TAILQ_INSERT_HEAD(chans, tmp, next_id);
    }
    free(ids);
}

static void add_user_list(struct user_list *usrs, char *line)
{
    idd_t *tmp;
    char **ids = parse_string(line, "\a");

    if (!ids)
        return;
    TAILQ_INIT(usrs);
    for (int i = 1; ids[i]; ++i) {
        tmp = create_id(ids[i]);
        TAILQ_INSERT_HEAD(usrs, tmp, next_id);
    }
    free(ids);
}

static void add_parsed_team(server_t *server, char *line)
{
    team_t *team;
    char **parse = parse_string(line, "\b");
    int i = 0;

    if (!parse)
        return;
    for (; parse[i]; ++i);
    if (i == 5) {
        team = malloc(sizeof(team_t));
        copy_id(team->uid, parse[0]);
        team->name = malloc(sizeof(char) * (strlen(parse[1]) + 1));
        strcpy(team->name, parse[1]);
        team->description = malloc(sizeof(char) * (strlen(parse[2]) + 1));
        strcpy(team->description, parse[2]);
        add_channel_list(&team->channels, parse[3]);
        add_user_list(&team->users, parse[4]);
        TAILQ_INSERT_HEAD(&server->teams, team, next_team);
    }
    free(parse);
}

void parse_team(server_t *server, char *path)
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
        add_parsed_team(server, lines[i]);
    }
    free(file);
    free(lines);
}
