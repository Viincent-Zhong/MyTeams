/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** deal_thread
*/

#include "server.h"

bool thread_exist(server_t *server, char *channel_id, char *name)
{
    for (thread_t *thread = server->threads.tqh_first; thread != NULL;
    thread = thread->next_thread.tqe_next) {
        if (strcmp(thread->title, name) == 0 &&
        strcmp(thread->uid_channel, channel_id) == 0)
            return true;
    }
    return false;
}

bool thread_in_channel(server_t *server, char *channel_id, char *thread_id)
{
    thread_t *tmp = get_thread(server, thread_id);

    if (tmp && strcmp(tmp->uid_channel, channel_id) == 0)
        return true;
    return false;
}

thread_t *get_thread(server_t *server, char *uid)
{
    for (thread_t *thread = server->threads.tqh_first; thread != NULL;
    thread = thread->next_thread.tqe_next) {
        if (strcmp(thread->uid, uid) == 0)
            return thread;
    }
    return NULL;
}

thread_t *create_new_thread(server_t *server, char **params)
{
    thread_t *new_thr;
    channel_t *chan;
    idd_t *tmp;

    if (!(chan = get_channel(server, params[0])))
        return NULL;
    new_thr = malloc(sizeof(thread_t));
    TAILQ_INIT(&new_thr->texts);
    generate_uuid(new_thr->uid);
    copy_id(new_thr->uid_channel, params[0]);
    copy_id(new_thr->uid_user, params[3]);
    new_thr->title = malloc(sizeof(char) * (strlen(params[1]) + 1));
    strcpy(new_thr->title, params[1]);
    new_thr->body = malloc(sizeof(char) * (strlen(params[2]) + 1));
    strcpy(new_thr->body, params[2]);
    new_thr->timestamp = time(NULL);
    tmp = create_id(new_thr->uid);
    TAILQ_INSERT_HEAD(&chan->threads, tmp, next_id);
    TAILQ_INSERT_HEAD(&server->threads, new_thr, next_thread);
    return new_thr;
}
