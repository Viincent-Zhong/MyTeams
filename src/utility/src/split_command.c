/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** split_command
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int count_quote(char *str)
{
    unsigned int count = 0;

    for (unsigned int i = 0; str[i]; ++i)
        if (str[i] == '\"')
            ++count;
    return count;
}

static char *capture_in_quote(char *str, int *i)
{
    char *new;
    unsigned int len = 0;

    for (unsigned int x = *i; str[x] != '\"'; ++x, ++len)
        if (str[x] == '\0' || str[x] == '\n' || str[x] == '\r')
            return NULL;
    new = malloc(sizeof(char) * (len + 1));
    if (new == NULL)
        return new;
    for (unsigned int x = 0; str[*i] != '\"'; ++(*i), ++x)
        new[x] = str[*i];
    new[len] = '\0';
    return new;
}

static char *capture_cmd(char *str, int *i)
{
    char *cmd;
    int len = 0;

    for (int x = *i; str[x] && str[x] != ' ' && str[x] != '\t'; ++x, ++len)
        if (str[x] == '\n' || str[x] == '\r')
            break;
    cmd = malloc(sizeof(char) * (len + 1));
    if (cmd == NULL)
        return NULL;
    for (int x = 0; str[*i] && str[*i] != ' ' &&
    str[*i] != '\t'; ++(*i), ++x) {
        if (str[*i] == '\n' || str[*i] == '\r')
            break;
        cmd[x] = str[*i];
    }
    cmd[len] = '\0';
    return cmd;
}

char **capture_command(char *str)
{
    char **cmd = malloc(sizeof(char *) * (3));
    int len = 0;
    int i = 0;

    if (cmd == NULL)
        return NULL;
    for (int i = 0; i < 3; cmd[i] = NULL, ++i);
    if ((cmd[0] = capture_cmd(str, &i)) == NULL)
        return cmd;
    for (; str[i] == ' ' || str[i] == '\n' || str[i] == '\r'
    || str[i] == '\t'; ++i);
    if ((len = strlen(str) - i) <= 0)
        return cmd;
    if ((cmd[1] = malloc(sizeof(char) * (len + 1))) == NULL)
        return cmd;
    for (int j = 0; str[i]; ++i, ++j)
        cmd[1][j] = str[i];
    cmd[1][len] = '\0';
    return cmd;
}

char **capture_args(char *str)
{
    char **cmd;
    int i = 0;
    unsigned int count = count_quote(str);

    if (count == 0 || count % 2 != 0)
        return NULL;
    cmd = malloc(sizeof(char *) * (count / 2 + 1));
    for (int x = 0; str[i]; ++i) {
        if (str[i] == '\"') {
            ++i;
            cmd[x] = capture_in_quote(str, &i);
            ++x;
        }
    }
    cmd[count / 2] = NULL;
    return cmd;
}
