/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** save_users
*/

#include "server.h"

void save_user(server_t *server, char *path)
{
    FILE *file = fopen(path, "w+");

    if (file == NULL)
        return;
    fwrite("id\bname\blist_associated_team\blist_associated_convs\n",
    51, 1, file);
    for (user_t *usr = server->users.tqh_first; usr != NULL;
    usr = usr->next_user.tqe_next) {
        fprintf(file, "%s\b%s\b", usr->uid, usr->name);
        save_id_list(usr->teams.tqh_first, file);
        fwrite("\b", 1, 1, file);
        save_id_list(usr->convs.tqh_first, file);
        fwrite("\n", 1, 1, file);
    }
    fclose(file);
}
