/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** cli_command.h
*/

#ifndef CLI_COMMAND_H_
    #define CLI_COMMAND_H_

    #include "client.h"

typedef int (*fct_command)(user_info_t *, char *);

typedef struct fct_pointer_s {
    char *command;
    fct_command fct;
} fct_pointer_t;

int help(user_info_t *user, char *args);
int login(user_info_t *user, char *args);
int logout(user_info_t *user, char *args);
int users(user_info_t *user, char *args);
int user_fct(user_info_t *user, char *args);
int send_fct(user_info_t *user, char *args);
int messages(user_info_t *user, char *args);
int subscribe(user_info_t *user, char *args);
int subscribed(user_info_t *user, char *args);
int unsubscribe(user_info_t *user, char *args);
int use(user_info_t *user, char *args);
int create(user_info_t *user, char *args);
int list(user_info_t *user, char *args);
int info(user_info_t *user, char *args);
int unknow(user_info_t *user, char *args);

#endif /* !CLI_COMMAND_H_ */
