/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** save_teams
*/

#include "server.h"

void save_team(server_t *server, char *path)
{
    FILE *file = fopen(path, "w+");

    if (file == NULL)
        return;
    fwrite("id\bname\bdescription\blist_id_channel\blist_id_user\n",
    49, 1, file);
    for (team_t *ts = server->teams.tqh_first; ts != NULL;
    ts = ts->next_team.tqe_next) {
        fprintf(file, "%s\b%s\b%s\b", ts->uid, ts->name, ts->description);
        save_id_list(ts->channels.tqh_first, file);
        fwrite("\b", 1, 1, file);
        save_id_list(ts->users.tqh_first, file);
        fwrite("\n", 1, 1, file);
    }
    fclose(file);
}
