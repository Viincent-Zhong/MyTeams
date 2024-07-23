/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** free_public
*/

#include "server.h"

static void free_teams(server_t *serv)
{
    for (team_t *tmp = TAILQ_FIRST(&serv->teams); tmp;
    tmp = TAILQ_FIRST(&serv->teams)) {
        for (idd_t *usr = TAILQ_FIRST(&tmp->users); usr;
        usr = TAILQ_FIRST(&tmp->users)) {
            TAILQ_REMOVE(&tmp->users, usr, next_id);
            free(usr);
        }
        for (idd_t *ch = TAILQ_FIRST(&tmp->channels); ch;
        ch = TAILQ_FIRST(&tmp->channels)) {
            TAILQ_REMOVE(&tmp->channels, ch, next_id);
            free(ch);
        }
        TAILQ_REMOVE(&serv->teams, tmp, next_team);
        free(tmp->name);
        free(tmp->description);
        free(tmp);
    }
}

static void free_users(server_t *serv)
{
    for (user_t *tmp = TAILQ_FIRST(&serv->users); tmp;
    tmp = TAILQ_FIRST(&serv->users)) {
        for (idd_t *cv = TAILQ_FIRST(&tmp->convs); cv;
        cv = TAILQ_FIRST(&tmp->convs)) {
            TAILQ_REMOVE(&tmp->convs, cv, next_id);
            free(cv);
        }
        for (idd_t *ts = TAILQ_FIRST(&tmp->teams); ts;
        ts = TAILQ_FIRST(&tmp->teams)) {
            TAILQ_REMOVE(&tmp->teams, ts, next_id);
            free(ts);
        }
        TAILQ_REMOVE(&serv->users, tmp, next_user);
        free(tmp->name);
        free(tmp);
    }
}

static void free_channels(server_t *serv)
{
    for (channel_t *tmp = TAILQ_FIRST(&serv->channels); tmp;
    tmp = TAILQ_FIRST(&serv->channels)) {
        for (idd_t *thr = TAILQ_FIRST(&tmp->threads); thr;
        thr = TAILQ_FIRST(&tmp->threads)) {
            TAILQ_REMOVE(&tmp->threads, thr, next_id);
            free(thr);
        }
        TAILQ_REMOVE(&serv->channels, tmp, next_channel);
        free(tmp->name);
        free(tmp->description);
        free(tmp);
    }
}

static void free_threads(server_t *serv)
{
    for (thread_t *tmp = TAILQ_FIRST(&serv->threads); tmp;
    tmp = TAILQ_FIRST(&serv->threads)) {
        for (idd_t *txt = TAILQ_FIRST(&tmp->texts); txt;
        txt = TAILQ_FIRST(&tmp->texts)) {
            TAILQ_REMOVE(&tmp->texts, txt, next_id);
            free(txt);
        }
        free(tmp->title);
        free(tmp->body);
        TAILQ_REMOVE(&serv->threads, tmp, next_thread);
        free(tmp);
    }
}

void free_groups(server_t *serv)
{
    free_threads(serv);
    free_users(serv);
    free_channels(serv);
    free_teams(serv);
}
