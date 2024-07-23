/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** save_conversation
*/

#include "server.h"

void save_conversations(server_t *server, char *path)
{
    FILE *file = fopen(path, "w+");

    if (file == NULL)
        return;
    fwrite("id\blist_of_id_message\n", 22, 1, file);
    for (conversation_t *conv = server->convs.tqh_first; conv != NULL;
    conv = conv->next_conv.tqe_next) {
        fprintf(file, "%s\b", conv->uid);
        save_id_list(conv->messages.tqh_first, file);
        fwrite("\n", 1, 1, file);
    }
    fclose(file);
}
