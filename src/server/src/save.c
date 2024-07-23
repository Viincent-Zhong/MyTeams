/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** save
*/

#include "server.h"

void save_id_list(idd_t *id, FILE *file)
{
    fwrite("id\a", 3, 1, file);
    for (; id != NULL; id = id->next_id.tqe_next)
        fprintf(file, "%s\a", id->uid);
}

void save_all(server_t *server)
{
    save_channel(server, CHANNEL_PATH);
    save_conversations(server, CONV_PATH);
    save_message(server, MESSAGE_PATH);
    save_team(server, TEAM_PATH);
    save_text(server, TEXT_PATH);
    save_thread(server, THREAD_PATH);
    save_user(server, USER_PATH);
}
