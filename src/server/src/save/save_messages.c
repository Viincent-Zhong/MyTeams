/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** save_messages
*/

#include "server.h"

void save_message(server_t *server, char *path)
{
    FILE *file = fopen(path, "w+");

    if (file == NULL)
        return;
    fwrite("id\bid_sender\bid_receptor\bmessage\btimestamp\n", 43, 1, file);
    for (message_t *msg = server->messages.tqh_first; msg != NULL;
    msg = msg->next_message.tqe_next) {
        fprintf(file, "%s\b%s\b%s\b%s\b%ld\n", msg->uid, msg->uid_send,
        msg->uid_receive, msg->message, msg->timestamp);
    }
    fclose(file);
}
