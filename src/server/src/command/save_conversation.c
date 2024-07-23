/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** save_conversation.c
*/

#include <stdio.h>
#include <unistd.h>
#include "logging_server.h"
#include "server.h"

static bool error_handling(server_t *server, client_t *client, command_t
*command)
{
    command_t send = {0};

    if (command->ac != 2)
        send.code = 500;
    if (send.code == 0 && !user_exists(server, command->av[0])) {
        strcat(send.av[0], command->av[0]);
        send.code = 503;
    }
    if (send.code != 0) {
        send.ac = 1;
        send_ping(&server->net, client->clid.fd, &send);
        return false;
    }
    return true;
}

void create_message(server_t *server, client_t *client, command_t *command)
{
    message_t *message;

    message = malloc(sizeof(message_t));
    generate_uuid(message->uid);
    copy_id(message->uid_receive, command->av[0]);
    copy_id(message->uid_send, client->user->uid);
    message->timestamp = time(NULL);
    message->message = malloc(sizeof(char) * (strlen(command->av[1]) + 1));
    strcpy(message->message, command->av[1]);
    TAILQ_INSERT_HEAD(&server->messages, message, next_message);
}

void save_conversation(server_t *server, client_t *client, command_t *command)
{
    command_t send = {0};
    client_t *receiver;

    if (!error_handling(server, client, command))
        return;
    create_message(server, client, command);
    server_event_private_message_sended(client->user->uid,
    command->av[0], command->av[1]);
    receiver = get_connected_user(server, command->av[0]);
    if (!receiver)
        return;
    send.code = 205;
    send.ac = 2;
    strcat(send.av[0], client->user->uid);
    strcat(send.av[1], command->av[1]);
    send_ping(&server->net, receiver->clid.fd, &send);
}
