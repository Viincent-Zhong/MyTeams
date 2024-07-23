/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** save_texts
*/

#include "server.h"

void save_text(server_t *server, char *path)
{
    FILE *file = fopen(path, "w+");

    if (file == NULL)
        return;
    fwrite("id\bid_associated_thread\bid_sender\bmessage\btimestamp\n",
    52, 1, file);
    for (text_t *txt = server->texts.tqh_first; txt != NULL;
    txt = txt->next_text.tqe_next) {
        fprintf(file, "%s\b%s\b%s\b%s\b%ld\n", txt->uid, txt->uid_thread,
        txt->uid_sender, txt->message, txt->timestamp);
    }
    fclose(file);
}
