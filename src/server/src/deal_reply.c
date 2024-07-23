/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** deal_reply
*/

#include "server.h"
#include "logging_server.h"

text_t *create_reply(server_t *server, char *thread_id, char *reply,
char *user_id)
{
    text_t *txt;
    thread_t *thr;
    idd_t *tmp;

    if (!(thr = get_thread(server, thread_id)))
        return NULL;
    txt = malloc(sizeof(text_t));
    generate_uuid(txt->uid);
    copy_id(txt->uid_sender, user_id);
    copy_id(txt->uid_thread, thread_id);
    txt->message = malloc(sizeof(char) * (strlen(reply) + 1));
    strcpy(txt->message, reply);
    txt->timestamp = time(NULL);
    tmp = create_id(txt->uid);
    TAILQ_INSERT_HEAD(&thr->texts, tmp, next_id);
    TAILQ_INSERT_HEAD(&server->texts, txt, next_text);
    return txt;
}
