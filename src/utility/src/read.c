/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** read
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"

command_t read_client(const unsigned int fd)
{
    command_t response = {0};

    if (read(fd, &response, sizeof(command_t)) <= 0) {
        response.code = -1;
        return response;
    }
    return response;
}

response_t read_server(const unsigned int fd)
{
    response_t response = {0};

    if (read(fd, &response, sizeof(response_t)) <= 0) {
        response.code = -1;
        return response;
    }
    return response;
}

char *read_input(unsigned int fd)
{
    char buff[1024] = {0};
    char *str;

    if (read(0, buff, sizeof(buff)) <= 0)
        return NULL;
    if (buff[0] == EOF)
        return NULL;
    str = malloc(sizeof(buff));
    strcpy(str, buff);
    return str;
}

char **parse_string(char *str, const char *delim)
{
    char **new_str = NULL;
    char *parsed;
    int occu = 1;

    if (!str)
        return NULL;
    for (int i = 0; str[i]; ++i)
        if (str[i] == delim[0])
            ++occu;
    parsed = strtok(str, delim);
    new_str = malloc(sizeof(char *) * (occu + 1));
    if (new_str == NULL)
        return NULL;
    memset(new_str, 0, sizeof(char *) * (occu + 1));
    for (int i = 0; parsed != NULL; ++i) {
        new_str[i] = parsed;
        parsed = strtok(NULL, delim);
    }
    return new_str;
}
