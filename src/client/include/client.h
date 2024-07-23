/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** client.h
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <stdbool.h>
    #include <sys/select.h>
    #include <sys/time.h>
    #include <uuid/uuid.h>
    #include "utils.h"

typedef struct user_info_s {
    serv_info_t server;
    context_t context;
    char *name;
    char uid[UUID_STR_LEN];
    char team_uuid[UUID_STR_LEN];
    char channel_uuid[UUID_STR_LEN];
    char thread_uuid[UUID_STR_LEN];
    unsigned int id;
    bool connected;
} user_info_t;

int client(int ac, char **av);
int init_client(int ac, char **av, user_info_t *user);
int get_command(user_info_t *user);
int unknow_msg(void);
int decrypt_announce(command_t *response, user_info_t *user);
void norm_three_good_announce(command_t *response, user_info_t *user);
void norm_two_good_announce(command_t *response, user_info_t *user);
void norm_one_good_announce(command_t *response, user_info_t *user);

#endif /* !CLIENT_H_ */
