/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** deal_channel
*/

#include "server.h"

bool channel_in_team(server_t *server, char *team_id, char *channel_id)
{
    channel_t *tmp = get_channel(server, channel_id);

    if (tmp && strcmp(tmp->uid_team, team_id) == 0)
        return true;
    return false;
}

bool channel_exist(server_t *server, char *team_uid, char *name)
{
    for (channel_t *channel = server->channels.tqh_first; channel != NULL;
    channel = channel->next_channel.tqe_next) {
        if (strcmp(channel->name, name) == 0 &&
        strcmp(channel->uid_team, team_uid) == 0)
            return true;
    }
    return false;
}

channel_t *get_channel(server_t *server, char *uid)
{
    for (channel_t *channel = server->channels.tqh_first; channel != NULL;
    channel = channel->next_channel.tqe_next) {
        if (strcmp(channel->uid, uid) == 0)
            return channel;
    }
    return NULL;
}

char *create_new_channel(server_t *server, char *name, char *description,
char *team_uid)
{
    channel_t *new_chan;
    team_t *team;
    idd_t *tmp;

    if ((team = get_team(server, team_uid)) == NULL)
        return NULL;
    new_chan = malloc(sizeof(channel_t));
    generate_uuid(new_chan->uid);
    TAILQ_INIT(&new_chan->threads);
    strcpy(new_chan->uid_team, team_uid);
    new_chan->name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new_chan->name, name);
    new_chan->description = malloc(sizeof(char) * (strlen(description) + 1));
    strcpy(new_chan->description, description);
    tmp = create_id(new_chan->uid);
    TAILQ_INSERT_HEAD(&team->channels, tmp, next_id);
    TAILQ_INSERT_HEAD(&server->channels, new_chan, next_channel);
    return new_chan->uid;
}
