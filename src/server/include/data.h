/*
** EPITECH PROJECT, 2022
** Project myteams
** File description:
** data.h
*/

#ifndef DATA_H_
    #define DATA_H_

    #include <sys/queue.h>
    #include <stdbool.h>
    #include <uuid/uuid.h>

    #define CHANNEL_PATH "data/channels.csv"
    #define CONV_PATH "data/conversations.csv"
    #define MESSAGE_PATH "data/messages.csv"
    #define TEAM_PATH "data/teams.csv"
    #define TEXT_PATH "data/texts.csv"
    #define THREAD_PATH "data/threads.csv"
    #define USER_PATH "data/users.csv"


typedef struct idd_t {
    char uid[UUID_STR_LEN];
    TAILQ_ENTRY(idd_t) next_id;
} idd_t;

typedef struct text_t {
    char uid[UUID_STR_LEN];
    char uid_thread[UUID_STR_LEN];
    char uid_sender[UUID_STR_LEN];
    char *message;
    time_t timestamp;
    TAILQ_ENTRY(text_t) next_text;
} text_t;

typedef struct thread_t {
    TAILQ_HEAD(text_list, idd_t) texts;
    char uid[UUID_STR_LEN];
    char uid_channel[UUID_STR_LEN];
    char uid_user[UUID_STR_LEN];
    char *title;
    char *body;
    time_t timestamp;

    TAILQ_ENTRY(thread_t) next_thread;
} thread_t;

typedef struct channel_t {
    TAILQ_HEAD(thread_list, idd_t) threads;
    char *description;
    char *name;
    char uid[UUID_STR_LEN];
    char uid_team[UUID_STR_LEN];

    TAILQ_ENTRY(channel_t) next_channel;
} channel_t;

typedef struct team_t {
    TAILQ_HEAD(channel_list, idd_t) channels;
    TAILQ_HEAD(user_list, idd_t) users;
    char *name;
    char *description;
    char uid[UUID_STR_LEN];
    TAILQ_ENTRY(team_t) next_team;
} team_t;

typedef struct user_t {
    TAILQ_HEAD(team_list, idd_t) teams;
    TAILQ_HEAD(conv_list, idd_t) convs;
    char *name;
    char uid[UUID_STR_LEN];
    bool is_connected;
    context_t context;

    TAILQ_ENTRY(user_t) next_user;
} user_t;

typedef struct message_t {
    char uid[UUID_STR_LEN];
    char uid_send[UUID_STR_LEN];
    char uid_receive[UUID_STR_LEN];
    char *message;
    time_t timestamp;

    TAILQ_ENTRY(message_t) next_message;
} message_t;

typedef struct conversation_t {
    TAILQ_HEAD(message_list, idd_t) messages;
    char uid[UUID_STR_LEN];
    TAILQ_ENTRY(conversation_t) next_conv;
} conversation_t;

#endif /* !DATA_H_ */
