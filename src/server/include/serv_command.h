/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** serv_command.h
*/

#ifndef SERV_COMMAND_H_
    #define SERV_COMMAND_H_

    #include "server.h"

typedef void (*fct_command)(server_t *server, client_t *client,
command_t *data);

typedef struct fct_pointer_s {
    int action;
    fct_command fct;
} fct_pointer_t;

void create_team(server_t *server, client_t *client, command_t *data);
void joining_team(server_t *server, client_t *client, command_t *data);
void leaving_team(server_t *server, client_t *client, command_t *data);
void create_thread(server_t *server, client_t *client, command_t *data);
void create_channel(server_t *server, client_t *client, command_t *data);
void create_comment(server_t *server, client_t *client, command_t *data);
void save_data(server_t *server, client_t *client, command_t *data);
void restore_data(server_t *server, client_t *client, command_t *data);
void save_conversation(server_t *server, client_t *client, command_t *data);
void restore_conversation(server_t *server, client_t *client, command_t *data);
void login_user(server_t *server, client_t *client, command_t *data);
void logout_user(server_t *server, client_t *client, command_t *data);
void info_user(server_t *server, client_t *client, command_t *data);
void info_team(server_t *server, client_t *client, command_t *data);
void info_channel(server_t *server, client_t *client, command_t *data);
void info_thread(server_t *server, client_t *client, command_t *data);
void list_users(server_t *server, client_t *client, command_t *data);

#endif /* !SERV_COMMAND_H_ */
