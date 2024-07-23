/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** restore_conversation.c
*/

#include <stdio.h>
#include <unistd.h>
#include "server.h"

static bool error_handling(server_t *server, client_t *client, command_t
*command)
{
    command_t send = {0};

    if (command->ac != 1)
        send.code = 500;
    if (send.code == 0 && !user_exists(server, command->av[0])) {
        strcat(send.av[0], command->av[0]);
        send.code = 503;
        send.ac = 1;
    }
    if (send.code != 0) {
        send_ping(&server->net, client->clid.fd, &send);
        return false;
    }
    return true;
}

void restore_conversation(server_t *server, client_t *client,
command_t *command)
{
    command_t send = {0};

    if (!error_handling(server, client, command))
        return;
    send.code = 300;
    send.ac = 3;
    for (message_t *msg = server->messages.tqh_first; msg != NULL;
    msg = msg->next_message.tqe_next) {
        if ((strcmp(msg->uid_send, command->av[0]) == 0 &&
        strcmp(msg->uid_receive, client->user->uid) == 0) ||
        (strcmp(msg->uid_receive, command->av[0]) == 0 &&
        strcmp(msg->uid_send, client->user->uid) == 0)) {
            strcpy(send.av[0], msg->uid_send);
            sprintf(send.av[1], "%ld", msg->timestamp);
            strcpy(send.av[2], msg->message);
            send_ping(&server->net, client->clid.fd, &send);
        }
    }
}
