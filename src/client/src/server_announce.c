/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** server_announce
*/

#include <stdio.h>
#include <stdlib.h>
#include "logging_client.h"
#include "client.h"

static bool norm_error_announce(command_t *response)
{
    switch (response->code) {
        case 505:
            client_error_unknown_channel(response->av[0]);
            return false;
        case 506:
            client_error_unknown_thread(response->av[0]);
            return false;
        case 507:
            printf("No reply\n");
            return false;
        case 430:
            client_error_already_exist();
            return false;
    }
    return true;
}

static bool error_announce(command_t *response)
{
    switch (response->code) {
        case 500:
            printf("Bad command\n");
            return false;
        case 501:
            printf("Already connected\n");
            return false;
        case 502:
            client_error_unauthorized();
            return false;
        case 503:
            client_error_unknown_user(response->av[0]);
            return false;
        case 504:
            client_error_unknown_team(response->av[0]);
            return false;
    }
    return norm_error_announce(response);
}

static void good_announce(command_t *response, user_info_t *user)
{
    switch (response->code) {
        case 200:
            break;
        case 201:
            break;
        case 202:
            client_print_users(response->av[0], response->av[1],
            atoi(response->av[2]));
            break;
        case 203:
            client_print_subscribed(response->av[0], response->av[1]);
            break;
        case 204:
            client_print_unsubscribed(response->av[0], response->av[1]);
            break;
    }
    norm_one_good_announce(response, user);
}

int decrypt_announce(command_t *response, user_info_t *user)
{
    if (!error_announce(response))
        return 0;
    good_announce(response, user);
    return 0;
}

int unknow_msg(void)
{
    printf("\
    ================\n\
    code: 500\n\
    message: UNKNOW ACTION\n\
    ================\n");
    return 0;
}
