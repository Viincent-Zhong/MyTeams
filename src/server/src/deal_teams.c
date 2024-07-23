/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** deal_teams
*/

#include "server.h"

bool is_subscribed(server_t *server, char *team_id, char *user_id)
{
    team_t *team = server->teams.tqh_first;

    for (; team != NULL; team = team->next_team.tqe_next)
        if (strcmp(team->uid, team_id) == 0)
            break;
    if (!team)
        return false;
    for (idd_t *usr = team->users.tqh_first; usr != NULL;
    usr = usr->next_id.tqe_next)
        if (strcmp(usr->uid, user_id) == 0)
            return true;
    return false;
}

bool team_exist(server_t *server, char *name)
{
    for (team_t *team = server->teams.tqh_first; team != NULL;
    team = team->next_team.tqe_next) {
        if (strcmp(team->uid, name) == 0)
            return true;
    }
    return false;
}

team_t *get_team(server_t *server, char *uid)
{
    for (team_t *team = server->teams.tqh_first; team != NULL;
    team = team->next_team.tqe_next) {
        if (strcmp(team->uid, uid) == 0)
            return team;
    }
    return NULL;
}

char *create_new_team(server_t *server, char *name, char *description,
char *user_uid)
{
    team_t *new_team = malloc(sizeof(team_t));
    idd_t *tmp;
    user_t *usr;

    TAILQ_INIT(&new_team->users);
    TAILQ_INIT(&new_team->channels);
    generate_uuid(new_team->uid);
    new_team->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new_team->name, name);
    new_team->description = malloc(sizeof(char) * (strlen(description) + 1));
    strcpy(new_team->description, description);
    tmp = create_id(user_uid);
    TAILQ_INSERT_HEAD(&new_team->users, tmp, next_id);
    TAILQ_INSERT_HEAD(&server->teams, new_team, next_team);
    usr = get_user(server, user_uid);
    if (usr) {
        tmp = create_id(new_team->uid);
        TAILQ_INSERT_HEAD(&usr->teams, tmp, next_id);
    }
    return new_team->uid;
}