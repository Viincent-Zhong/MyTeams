/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** server.h
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include <sys/select.h>
    #include <unistd.h>
    #include <sys/queue.h>
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "utils.h"
    #include "data.h"

    #define GOOD_EXIT   0
    #define BAD_EXIT    -1

typedef struct net_s {
    fd_set rdfs;
    fd_set wdfs;
    fd_set edfs;
    int max_fd;
} net_t;

typedef struct client_t {
    socket_t clid;
    context_t context;
    user_t *user;
    TAILQ_ENTRY(client_t) next_client;
} client_t;

typedef struct server_s {
    net_t net;
    socket_t serv;
    TAILQ_HEAD(client_list, client_t) clid_head;

    TAILQ_HEAD(, text_t) texts;
    TAILQ_HEAD(, thread_t) threads;
    TAILQ_HEAD(, channel_t) channels;
    TAILQ_HEAD(, team_t) teams;
    TAILQ_HEAD(, user_t) users;
    TAILQ_HEAD(, message_t) messages;
    TAILQ_HEAD(, conversation_t) convs;
} server_t;

int server(int ac, char **av);
void quit_dog(server_t *serv, client_t *client);
void client_connection(server_t *server, socket_t *client, socket_t serv);
int detect_clients(server_t *serv);
void exec_command(server_t *serv, client_t *client, command_t *command);
void send_status_msg(net_t *serv, int fd, int status, char *msg);
void generate_user(user_t *user, const char *name);
int select_whole_server(server_t *serv);
void free_server(server_t *serv);


void copy_id(char *uid, char *copy);
time_t str_to_time(const char *str);
int parse_all(server_t *server);
void parse_channel(server_t *server, char *path);
void parse_conversation(server_t *server, char *path);
void parse_message(server_t *server, char *path);
void parse_team(server_t *server, char *path);
void parse_text(server_t *server, char *path);
void parse_thread(server_t *server, char *path);
void parse_user(server_t *server, char *path);
idd_t *create_id(char *uid);

void save_id_list(idd_t *id, FILE *file);
void save_all(server_t *server);
void save_channel(server_t *server, char *path);
void save_conversations(server_t *server, char *path);
void save_message(server_t *server, char *path);
void save_team(server_t *server, char *path);
void save_text(server_t *server, char *path);
void save_thread(server_t *server, char *path);
void save_user(server_t *server, char *path);

void free_messages(server_t *serv);
void free_groups(server_t *serv);

user_t *get_user(server_t *serv, char *user_id);

bool team_exist(server_t *server, char *name);
char *create_new_team(server_t *server, char *name, char *description,
char *user_uid);
team_t *get_team(server_t *server, char *uid);
bool is_subscribed(server_t *server, char *team_id, char *user_id);

bool channel_in_team(server_t *server, char *team_id, char *channel_id);
bool channel_exist(server_t *server, char *team_uid, char *name);
char *create_new_channel(server_t *server, char *name, char *description,
char *team_uid);
channel_t *get_channel(server_t *server, char *uid);

bool thread_in_channel(server_t *server, char *channel_id, char *thread_id);
bool thread_exist(server_t *server, char *channel_id, char *name);
thread_t *create_new_thread(server_t *server, char **params);
thread_t *get_thread(server_t *server, char *uid);

text_t *create_reply(server_t *server, char *thread_id, char *reply,
char *user_id);
client_t *get_connected_user(server_t *serv, char *user_id);
bool user_is_connected(server_t *serv, char *user_id);
bool user_exists(server_t *server, char *user_id);
user_t *get_username(server_t *server, char *name);

void send_ping(net_t *serv, int fd, command_t *send);
void ping_all_user(server_t *serv, command_t *send);
void ping_team_users(server_t *server, command_t *send, team_t *team);

#endif /* !SERVER_H_ */
