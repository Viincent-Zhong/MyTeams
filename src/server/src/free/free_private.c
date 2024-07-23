/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** free_private
*/

#include "server.h"

static void free_texts(server_t *serv)
{
    for (text_t *tmp = TAILQ_FIRST(&serv->texts); tmp;
    tmp = TAILQ_FIRST(&serv->texts)) {
        TAILQ_REMOVE(&serv->texts, tmp, next_text);
        free(tmp->message);
        free(tmp);
    }
    for (message_t *tmp = TAILQ_FIRST(&serv->messages); tmp;
    tmp = TAILQ_FIRST(&serv->messages)) {
        TAILQ_REMOVE(&serv->messages, tmp, next_message);
        free(tmp->message);
        free(tmp);
    }
}

void free_messages(server_t *serv)
{
    for (conversation_t *tmp = TAILQ_FIRST(&serv->convs); tmp;
    tmp = TAILQ_FIRST(&serv->convs)) {
        for (idd_t *msg = TAILQ_FIRST(&tmp->messages); msg;
        msg = TAILQ_FIRST(&tmp->messages)) {
            TAILQ_REMOVE(&tmp->messages, msg, next_id);
            free(msg);
        }
        TAILQ_REMOVE(&serv->convs, tmp, next_conv);
        free(tmp);
    }
    free_texts(serv);
}
