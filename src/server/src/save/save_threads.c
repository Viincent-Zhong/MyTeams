/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** save_threads
*/

#include "server.h"

void save_thread(server_t *server, char *path)
{
    FILE *file = fopen(path, "w+");

    if (file == NULL)
        return;
    fwrite("id\bid_channel\blist_id_text\btitle\bbody\btimestamp\bid_user\n",
    56, 1, file);
    for (thread_t *thr = server->threads.tqh_first; thr != NULL;
    thr = thr->next_thread.tqe_next) {
        fprintf(file, "%s\b%s\b", thr->uid, thr->uid_channel);
        save_id_list(thr->texts.tqh_first, file);
        fprintf(file, "\b%s\b%s\b%ld\b%s", thr->title, thr->body,
        thr->timestamp, thr->uid_user);
        fwrite("\n", 1, 1, file);
    }
    fclose(file);
}
