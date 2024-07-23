/*
** EPITECH PROJECT, 2022
** Projet myteams
** File description:
** lib.c
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"

char **parse_command(char *command, const char *delim)
{
    char **new_command = NULL;
    char *parsed;
    int occu = 1;

    if (!command)
        return NULL;
    parsed = strtok(command, "\n\r");
    for (int i = 0; command[i]; ++i)
        if (command[i] == delim[0])
            ++occu;
    parsed = strtok(command, delim);
    new_command = malloc(sizeof(char *) * (occu + 1));
    if (new_command == NULL)
        return NULL;
    memset(new_command, 0, sizeof(char *) * (occu + 1));
    for (int i = 0; parsed != NULL; ++i) {
        new_command[i] = parsed;
        parsed = strtok(NULL, delim);
    }
    return new_command;
}

char *array_to_string(char **array)
{
    unsigned int size = 1;
    int spaces = -1;
    char *str;

    if (array == NULL || array[0] == NULL)
        return "";
    for (int i = 0; array[i] != NULL; ++i, ++spaces)
        size += strlen(array[i]);
    str = malloc(sizeof(char) * (size + (spaces + ((1 + spaces) * 2))));
    strcpy(str, "");
    for (int i = 0; array[i] != NULL; ++i, --spaces) {
        strcat(str, "\"");
        strcat(str, array[i]);
        strcat(str, "\"");
        if (spaces != 0)
            strcat(str, " ");
    }
    return str;
}

command_t format_message_to_server(action_server_t action, char *args)
{
    command_t msg = {0};
    char **av;
    int ac = 0;

    if (args == NULL || (av = capture_args(args)) == NULL) {
        msg.code = -1;
        return msg;
    }
    msg.code = action;
    for (int i = 0, len = 0; av[i] && i < 4; ++i, ++ac) {
        msg.av[i][0] = '\0';
        strcat(msg.av[i], av[i]);
        free(av[i]);
    }
    msg.ac = ac;
    free(av);
    return msg;
}

char *parse_message_to_server(action_server_t action, char *data)
{
    char *str;

    if (data != NULL) {
        str = malloc(sizeof(char) * (strlen(data) + 4));
        sprintf(str, "%d %s", action, data);
        free(data);
    } else {
        str = malloc(sizeof(char) * 4);
        sprintf(str, "%d", action, data);
    }
    return str;
}

char *get_file_content(const char *file)
{
    struct stat new_stat;
    int fd;
    char *buffer;
    int file_size;
    int size;

    stat(file, &new_stat);
    file_size = new_stat.st_size;
    buffer = malloc(sizeof(char) * (file_size + 1));
    if (buffer == NULL)
        return NULL;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (NULL);
    size = read(fd, buffer, file_size);
    if (size == 0)
        return (NULL);
    buffer[size] = '\0';
    close(fd);
    return (buffer);
}
