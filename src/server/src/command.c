/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** command
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "serv_command.h"

static const fct_pointer_t list[] = {
    {CREATE_TEAM, &create_team}, {JOINING_TEAM, &joining_team},
    {LEAVING_TEAM, &leaving_team}, {CREATE_THREAD, &create_thread},
    {CREATE_CHANNEL, &create_channel}, {CREATE_COMMENT, &create_comment},
    {SAVE_DATA, &save_data}, {RESTORE_DATA, &restore_data},
    {SAVE_CONVERSATION, &save_conversation},
    {RESTORE_CONVERSATION, &restore_conversation}, {LOGIN_CLIENT, &login_user},
    {LOGOUT_CLIENT, &logout_user}, {DATA_USERS, &info_user},
    {DATA_TEAMS, &info_team}, {DATA_CHANNEL, &info_channel},
    {DATA_THREAD, &info_thread}, {LIST_USER, list_users}, {UNKNOW, NULL}};

int select_whole_server(server_t *serv)
{
    FD_ZERO(&serv->net.rdfs);
    FD_ZERO(&serv->net.wdfs);
    FD_ZERO(&serv->net.edfs);
    FD_SET(serv->serv.fd, &serv->net.rdfs);
    for (client_t *np = serv->clid_head.tqh_first; np != NULL;
    np = np->next_client.tqe_next)
        FD_SET(np->clid.fd, &serv->net.rdfs);
    if (select(serv->net.max_fd + 1, &serv->net.rdfs,
        &serv->net.wdfs, &serv->net.edfs, NULL) == -1)
        return -1;
}

void exec_command(server_t *serv, client_t *client, command_t *command)
{
    for (int i = 0; list[i].fct != NULL; ++i)
        if (command->code == list[i].action) {
            list[i].fct(serv, client, command);
            return;
        }
    send_status_msg(&serv->net, client->clid.fd, 500, "UNKNOW ACTION\n");
}
