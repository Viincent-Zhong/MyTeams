/*
** EPITECH PROJECT, 2022
** myteams
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_

    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <sys/select.h>

typedef struct socket_s {
    struct sockaddr_in addr;
    int addrlen;
    int fd;
} socket_t;

typedef enum action_server {
    CREATE_TEAM = 1,
    JOINING_TEAM = 2,
    LEAVING_TEAM = 3,
    CREATE_THREAD = 4,
    CREATE_CHANNEL = 5,
    CREATE_COMMENT = 6,
    SAVE_DATA = 7,
    RESTORE_DATA = 8,
    SAVE_CONVERSATION = 9,
    RESTORE_CONVERSATION = 10,
    LOGIN_CLIENT = 11,
    LOGOUT_CLIENT = 12,
    DATA_USERS = 13,
    DATA_TEAMS = 14,
    DATA_CHANNEL = 15,
    DATA_THREAD = 16,
    LIST_USER = 17,
    UNKNOW = -1
} action_server_t;

typedef enum context_s {
    TEAM,
    CHANNEL,
    THREAD,
    REPLY
} context_t;

typedef struct serv_info_s {
    struct timeval timeout;
    fd_set rdfs;
    fd_set wdfs;
    unsigned int fd;
} serv_info_t;

typedef struct command_s {
    int code;
    int ac;
    char av[5][1024];
} command_t;

typedef struct response_s {
    int code;
    char response[1024];
} response_t;

int init_socket(socket_t *sock, int port);
void send_message(serv_info_t *serv, const command_t message);
char **parse_string(char *str, const char *delim);
char **parse_command(char *command, const char *delim);
char *array_to_string(char **array);
char *parse_message_to_server(action_server_t action, char *data);
char *get_file_content(const char *file);
void generate_uuid(char *uid);
char **split_command(char *str);

char **capture_args(char *str);
char **capture_command(char *str);
command_t format_message_to_server(action_server_t action, char *args);
command_t read_client(const unsigned int fd);
char *read_input(unsigned int fd);
response_t read_server(const unsigned int fd);

#endif /* !UTILS_H_ */
