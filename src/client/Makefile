##
## EPITECH PROJECT, 2022
## Project myteams
## File description:
## server Makefile
##

CC		=	gcc

UTIL_PATH	=	../utility/src

SRC_FILE	=	src/client.c				\
				src/init.c					\
				src/command/help.c			\
				src/command/login.c			\
				src/command/logout.c		\
				src/command/users.c			\
				src/command/user.c			\
				src/command/send.c			\
				src/command/messages.c		\
				src/command/subscribe.c		\
				src/command/subscribed.c	\
				src/command/unsubscribe.c	\
				src/command/use.c			\
				src/command/create.c		\
				src/command/list.c			\
				src/command/info.c			\
				src/command/unknow.c		\
				$(UTIL_PATH)/socket.c		\
				$(UTIL_PATH)/lib.c			\
				$(UTIL_PATH)/split_command.c\
				$(UTIL_PATH)/read.c			\
				src/get_command.c			\
				src/server_announce.c		\
				src/norm_announce.c			\

SRC			=	main.c						\
				${SRC_FILE}					\

T_SRC		=	tests/unit_test_client.c	\
				${SRC_FILE}					\

OBJ			=	$(SRC:.c=.o)

NAME		=	myteams_cli

T_NAME		=	unit_test

CFLAGS		=	-iquote ./include			\
				-iquote ../utility/include	\
				-iquote ../../libs/myteams	\
				-L../../libs/myteams


LDFLAGS		+=	--coverage -lcriterion

all:			$(NAME)

debug:			CFLAGS	+=	-g
debug:			$(NAME)

$(NAME):		$(OBJ)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -lmyteams -luuid

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)
				$(RM) $(T_NAME)

re:				fclean all

.PHONY:			all clean fclean re tests_run tclean $(NAME)
