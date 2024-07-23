/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** save_channels
*/

#include "server.h"

void save_channel(server_t *server, char *path)
{
    FILE *file = fopen(path, "w+");

    if (file == NULL)
        return;
    fwrite("id\bname\bdescription\bid_associated_team\blist_id_thread\n",
    54, 1, file);
    for (channel_t *channel = server->channels.tqh_first; channel != NULL;
    channel = channel->next_channel.tqe_next) {
        fprintf(file, "%s\b%s\b%s\b%s\b", channel->uid, channel->name,
        channel->description, channel->uid_team);
        save_id_list(channel->threads.tqh_first, file);
        fwrite("\n", 1, 1, file);
    }
    fclose(file);
}
