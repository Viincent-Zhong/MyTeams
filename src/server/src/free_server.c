/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** free_server
*/

#include <stdlib.h>
#include "server.h"

void free_server(server_t *serv)
{
    free_groups(serv);
    free_messages(serv);
    for (client_t *tmp = TAILQ_FIRST(&serv->clid_head); tmp;
    tmp = TAILQ_FIRST(&serv->clid_head)) {
        TAILQ_REMOVE(&serv->clid_head, tmp, next_client);
        close(tmp->clid.fd);
        free(tmp);
    }
}
