/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** get_command
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "cli_command.h"

static const fct_pointer_t tab[] = {
    {"/help", &help}, {"/login", &login}, {"/logout", &logout},
    {"/users", &users}, {"/user", &user_fct}, {"/send", &send_fct},
    {"/messages", &messages}, {"/subscribe", &subscribe},
    {"/subscribed", &subscribed}, {"/unsubscribe", &unsubscribe},
    {"/use", &use}, {"/create", &create}, {"/list", &list},
    {"/info", &info}, {NULL, NULL}};

static void free_array(char **array)
{
    free(array[0]);
    free(array);
}

static int execute_command(user_info_t *user, char *str)
{
    char **command = capture_command(str);
    int res = 0;
    int found = 0;

    if (command == NULL)
        return unknow(user, NULL);
    for (int i = 0; tab[i].command != NULL; ++i)
        if (strcmp(tab[i].command, command[0]) == 0) {
            res = tab[i].fct(user, command[1]);
            found = 1;
            break;
        }
    for (int i = 0; command[i]; ++i)
        free(command[i]);
    free(command);
    if (found == 1)
        return res;
    return unknow(user, NULL);
}

int get_command(user_info_t *user)
{
    char *line;

    if (!FD_ISSET(0, &user->server.rdfs))
        return 1;
    if ((line = read_input(STDIN_FILENO)) == NULL)
        return 0;
    if (strlen(line) == 1) {
        free(line);
        return 1;
    }
    line[strlen(line) - 1] = '\0';
    execute_command(user, line);
    free(line);
    return 1;
}
