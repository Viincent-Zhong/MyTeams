/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** norm_announce.c
*/

#include <stdlib.h>
#include "logging_client.h"
#include "client.h"

void norm_four_good_announce(command_t *response, user_info_t *user)
{
    switch (response->code) {
        case 322:
            client_event_logged_in(response->av[0], response->av[1]);
            break;
        case 323:
            client_event_logged_out(response->av[0], response->av[1]);
            break;
        case 324:
            client_event_channel_created(response->av[0], response->av[1],
            response->av[2]);
            break;
        case 325:
            client_event_thread_created(response->av[0], response->av[1],
            strtol(response->av[2], NULL, 10), response->av[3],
            response->av[4]);
    }
}

void norm_three_good_announce(command_t *response, user_info_t *user)
{
    switch (response->code) {
        case 311:
            client_print_team_created(response->av[0], response->av[1],
            response->av[2]);
            break;
        case 313:
            client_event_thread_reply_received(response->av[0],
            response->av[1], response->av[2], response->av[3]);
            break;
        case 320:
            client_print_teams(response->av[0], response->av[1],
            response->av[2]);
            break;
        case 321:
            client_print_channel(response->av[0], response->av[1],
            response->av[2]);
            break;
    }
    norm_four_good_announce(response, user);
}

void norm_two_good_announce(command_t *response, user_info_t *user)
{
    switch (response->code) {
        case 300:
            client_private_message_print_messages(response->av[0],
            strtol(response->av[1], NULL, 10), response->av[2]);
            break;
        case 301:
            client_print_teams(response->av[0], response->av[1],
            response->av[2]);
            break;
        case 302:
            client_print_users(response->av[0], response->av[1],
            atoi(response->av[2]));
            break;
        case 310:
            client_event_team_created(response->av[0], response->av[1],
            response->av[2]);
            break;
    }
    norm_three_good_announce(response, user);
}

void norm_one_good_announce(command_t *response, user_info_t *user)
{
    switch (response->code) {
        case 205:
            client_event_private_message_received(response->av[0],
            response->av[1]);
            break;
        case 211:
            client_print_channel_created(response->av[0], response->av[1],
            response->av[2]);
            break;
        case 212:
            client_print_thread_created(response->av[0], response->av[1],
            strtol(response->av[2], NULL, 10), response->av[3],
            response->av[4]);
            break;
        case 213:
            client_print_reply_created(response->av[0], response->av[1],
            strtol(response->av[2], NULL, 10), response->av[3]);
            break;
    }
    norm_two_good_announce(response, user);
}
