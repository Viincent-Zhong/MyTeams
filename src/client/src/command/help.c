/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** help.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "client.h"
#include "utils.h"

static void norm_print_message(void)
{
    dprintf(STDIN_FILENO, "\t/subscribed[\"team_uuid\"] : \
    ist all subscribed teams or list all users subscribed to a team\n");
    dprintf(STDIN_FILENO, "\t/unsubscribe[\"team_uuid\"] : \
    unsubscribe from a team\n");
    dprintf(STDIN_FILENO, "\t/use[\"team_uuid\"]?[\"channel_uuid\"]? \
    [\"thread_uuid\"]? : use specify a context team/channel/thread\n");
    dprintf(STDIN_FILENO, "\t/create : based on what is being used \
    create the sub resource\n");
    dprintf(STDIN_FILENO, "\t/list : based on what is being used \
    list all the sub resources\n");
    dprintf(STDIN_FILENO, "\t/info : based on what is being used \
    list all the sub resources\n");
}

static void print_message(void)
{
    dprintf(STDIN_FILENO, "\t/logout : disconnect from the server\n");
    dprintf(STDIN_FILENO, "\t/users : get list of all user that exists on \
    the domain\n");
    dprintf(STDIN_FILENO, "\t/user[\"user_uuid\"] : get information about \
    one user\n");
    dprintf(STDIN_FILENO, "\t/send[\"user_uuid\"] : send a message to \
    a user\n");
    dprintf(STDIN_FILENO, "\t/messages[\"user_uuid\"] : list all messages \
    exchange with an user\n");
    dprintf(STDIN_FILENO, "\t/subscribe[\"team_uuid\"] : subscribe to the \
    event of a team and its sub directories \
    (enable reception of all events from a team)\n");
    norm_print_message();
}

int help(user_info_t *user, char *args)
{
    dprintf(STDIN_FILENO, "HELP:\n");
    if (!user->connected)
        dprintf(STDIN_FILENO, "\tlogin [\"user_name\"]\n");
    else
        print_message();
    return 0;
}
