/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** unit_test_parse
*/

#include <criterion/criterion.h>
#include "server.h"

static void compare_team(team_t *team, char *id, char *name, char *desc, char *channs[], char *users[])
{
    int i = 0;

    cr_expect_str_eq(team->uid, id);
    cr_expect_str_eq(team->name, name);
    cr_expect_str_eq(team->description, desc);
    for (idd_t *np = team->channels.tqh_first; np != NULL; np = np->next_id.tqe_next, ++i)
        cr_expect_str_eq(np->uid, channs[i]);
    i = 0;

    for (idd_t *np = team->users.tqh_first; np != NULL; np = np->next_id.tqe_next, ++i)
        cr_expect_str_eq(np->uid, users[i]);
}

Test(good, parse_team)
{
    server_t server;

    TAILQ_INIT(&server.teams);
    parse_team(&server, "./parse_assets/team.csv");

    compare_team(server.teams.tqh_first, "2", "chien", "un dog", (char *[]){"9", "8", "7"}, (char *[]){"12", "11", "10"});
    compare_team(server.teams.tqh_first->next_team.tqe_next, "1", "dog", "un chien", (char *[]){"3", "2", "1"}, (char *[]){"6", "5", "4"});
}

Test(unknown_file, parse_team)
{
    server_t server;

    TAILQ_INIT(&server.teams);
    parse_team(&server, "./parse_assets/");

    cr_expect_eq(server.teams.tqh_first, NULL);
}

static void compare_user(user_t *user, char *id, char *name, char *teams[], char *convs[])
{
    int i = 0;

    cr_expect_str_eq(user->uid, id);
    cr_expect_str_eq(user->name, name);
    for (idd_t *np = user->teams.tqh_first; np != NULL; np = np->next_id.tqe_next, ++i)
        cr_expect_str_eq(np->uid, teams[i]);
    i = 0;
    for (idd_t *np = user->convs.tqh_first; np != NULL; np = np->next_id.tqe_next, ++i)
        cr_expect_str_eq(np->uid, convs[i]);
}

Test(good, parse_user)
{
    server_t server;

    TAILQ_INIT(&server.users);
    parse_user(&server, "./parse_assets/user.csv");
    compare_user(server.users.tqh_first, "3", "guillaume", (char *[]){"4", "3", "2" , "1"}, (char *[]){"4", "3", "2" , "1"});
    compare_user(server.users.tqh_first->next_user.tqe_next, "2", "pad", (char *[]){"4", "3", "2", "1"}, (char *[]){"4", "3", "2", "1"});
    compare_user(server.users.tqh_first->next_user.tqe_next->next_user.tqe_next, "1", "vincent", (char *[]){"4", "3", "2", "1"}, (char *[]){"4", "3", "2", "1"});
}

Test(unknown_file, parse_user)
{
    server_t server;

    TAILQ_INIT(&server.users);
    parse_user(&server, "./parse_assets/rien");
    cr_expect_eq(server.users.tqh_first, NULL);
}

static void compare_channel(channel_t *channel, char *id, char *name, char *desc, char *team, char *thread[])
{
    int i = 0;

    cr_expect_str_eq(channel->uid, id);
    cr_expect_str_eq(channel->name, name);
    cr_expect_str_eq(channel->description, desc);
    cr_expect_str_eq(channel->uid_team, team);
    for (idd_t *np = channel->threads.tqh_first; np != NULL; np = np->next_id.tqe_next, ++i)
        cr_expect_str_eq(np->uid, thread[i]);
}

Test(good, parse_channel)
{
    server_t server;

    TAILQ_INIT(&server.channels);
    parse_channel(&server, "./parse_assets/channel.csv");
    compare_channel(server.channels.tqh_first, "3", "myteam", "bagarre", "1", (char *[]){"4", "3", "2", "1"});
    compare_channel(server.channels.tqh_first->next_channel.tqe_next, "2", "myteams", "talk", "4", (char *[]){"8", "7", "6", "5"});
    compare_channel(server.channels.tqh_first->next_channel.tqe_next->next_channel.tqe_next, "1", "pasbien", "un channel x", "1", (char *[]){"4", "3", "2", "1"});
}

Test(unknown_file, parse_channel)
{
    server_t server;

    TAILQ_INIT(&server.channels);
    parse_channel(&server, "./parse_assets/dog");
    cr_expect_eq(server.channels.tqh_first, NULL);
}

static void compare_conv(conversation_t *conv, char *id, char *msg[])
{
    int i = 0;

    cr_expect_str_eq(conv->uid, id);
    for (idd_t *np = conv->messages.tqh_first; np != NULL; np = np->next_id.tqe_next, ++i)
        cr_expect_str_eq(np->uid, msg[i]);
}

Test(good, parse_conv)
{
    server_t server;

    TAILQ_INIT(&server.convs);
    parse_conversation(&server, "./parse_assets/conv.csv");
    compare_conv(server.convs.tqh_first, "3", (char *[]){"18","16","14","12","10"});
    compare_conv(server.convs.tqh_first->next_conv.tqe_next, "2", (char *[]){"4", "3", "2"});
    compare_conv(server.convs.tqh_first->next_conv.tqe_next->next_conv.tqe_next, "1", (char *[]){"1"});
}

Test(unknown_file, parse_conv)
{
    server_t server;

    TAILQ_INIT(&server.convs);
    parse_conversation(&server, "./parse_assets/what");
    cr_expect_eq(server.convs.tqh_first, NULL);
}

static void compare_thread(thread_t *thread, char *id, char *channel, char *text[])
{
    int i = 0;

    cr_expect_str_eq(thread->uid, id);
    cr_expect_str_eq(thread->uid_channel, channel);
    for (idd_t *np = thread->texts.tqh_first; np != NULL; np = np->next_id.tqe_next, ++i)
        cr_expect_str_eq(np->uid, text[i]);
}

Test(good, parse_thread)
{
    server_t server;

    TAILQ_INIT(&server.threads);
    parse_thread(&server, "./parse_assets/thread.csv");
    compare_thread(server.threads.tqh_first, "3", "1", (char *[]){"20", "10"});
    compare_thread(server.threads.tqh_first->next_thread.tqe_next, "2", "2",(char *[]){"5","4","3","2","1"});
    compare_thread(server.threads.tqh_first->next_thread.tqe_next->next_thread.tqe_next, "1", "3", (char *[]){"12345"});
}

Test(unknown_file, parse_thread)
{
    server_t server;

    TAILQ_INIT(&server.threads);
    parse_thread(&server, "./parse_assets/dog");
    cr_expect_eq(server.threads.tqh_first, NULL);
}

static void compare_message(message_t *msg, char *id, char *send, char *recep, char *message, time_t time)
{
    int i = 0;

    cr_expect_str_eq(msg->uid, id);
    cr_expect_str_eq(msg->uid_send, send);
    cr_expect_str_eq(msg->uid_receive, recep);
    cr_expect_str_eq(msg->message, message);
    cr_expect_eq(msg->timestamp, time);
}

Test(good, parse_message)
{
    server_t server;

    TAILQ_INIT(&server.messages);
    parse_message(&server, "./parse_assets/message.csv");
    compare_message(server.messages.tqh_first, "3", "1", "2", "salut bg", 123455);
    compare_message(server.messages.tqh_first->next_message.tqe_next, "2", "2", "3", "le id 1 il est con", 54886);
    compare_message(server.messages.tqh_first->next_message.tqe_next->next_message.tqe_next, "1", "3", "2", "javou c un idiot", 987652);
}

Test(unknown_file, parse_message)
{
    server_t server;

    TAILQ_INIT(&server.messages);
    parse_message(&server, "./parse_assets/wtf");
    cr_expect_eq(server.messages.tqh_first, NULL);
}

static void compare_text(text_t *msg, char *id, char *thread, char *send, char *message, time_t time)
{
    int i = 0;

    cr_expect_str_eq(msg->uid, id);
    cr_expect_str_eq(msg->uid_thread, thread);
    cr_expect_str_eq(msg->uid_sender, send);
    cr_expect_str_eq(msg->message, message);
    cr_expect_eq(msg->timestamp, time);
}

Test(good, parse_text)
{
    server_t server;

    TAILQ_INIT(&server.texts);
    parse_text(&server, "./parse_assets/text.csv");
    compare_text(server.texts.tqh_first, "3", "1", "2", "salut bg", 121234);
    compare_text(server.texts.tqh_first->next_text.tqe_next, "2", "2", "3", "le id 1 il est con", 356554);
    compare_text(server.texts.tqh_first->next_text.tqe_next->next_text.tqe_next, "1", "3", "2", "javou c un idiot", 231234);
}

Test(unknown_file, parse_text)
{
    server_t server;

    TAILQ_INIT(&server.texts);
    parse_text(&server, "./parse_assets/wtf");
    cr_expect_eq(server.texts.tqh_first, NULL);
}