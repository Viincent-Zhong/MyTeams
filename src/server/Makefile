##
## EPITECH PROJECT, 2022
## Project myteams
## File description:
## server Makefile
##

CC		=	gcc

UTIL_PATH	=	../utility/src

SRC_FILE	= 	src/server.c						\
			src/connection.c					\
			src/handle_client.c					\
			src/command.c						\
			src/command/create_channel.c		\
			src/command/create_comment.c		\
			src/command/create_team.c			\
			src/command/create_thread.c			\
			src/command/joining_team.c			\
			src/command/leaving_team.c			\
			src/command/restore_conversation.c	\
			src/command/restore_data.c			\
			src/command/save_conversation.c		\
			src/command/save_data.c				\
			src/command/login_user.c			\
			src/command/logout_user.c			\
			src/command/info_user.c			\
			src/command/info_team.c			\
			src/command/info_thread.c			\
			src/command/info_channel.c			\
			src/command/list_users.c			\
			src/parser.c						\
			src/parse/parse_channels.c			\
			src/parse/parse_conversations.c		\
			src/parse/parse_messages.c			\
			src/parse/parse_teams.c				\
			src/parse/parse_texts.c				\
			src/parse/parse_threads.c			\
			src/parse/parse_users.c				\
			src/save.c							\
			src/save/save_channels.c			\
			src/save/save_conversations.c		\
			src/save/save_messages.c			\
			src/save/save_teams.c				\
			src/save/save_texts.c				\
			src/save/save_threads.c				\
			src/save/save_users.c				\
			src/free_server.c					\
			$(UTIL_PATH)/socket.c				\
			$(UTIL_PATH)/lib.c					\
			$(UTIL_PATH)/split_command.c					\
			$(UTIL_PATH)/read.c					\
			src/deal_user.c	\
			src/free/free_private.c				\
			src/free/free_public.c				\
			src/deal_teams.c					\
			src/deal_channel.c					\
			src/deal_thread.c					\
			src/deal_reply.c					\
			src/deal_users.c					\

SRC		= 	main.c	\
			$(SRC_FILE)

T_SRC	=	tests/unit_test_server.c			\
			tests/unit_test_parse.c				\
			$(SRC_FILE)

OBJ		=	$(SRC:.c=.o)

NAME	=	myteams_server

T_NAME	=	unit_test

CFLAGS	=	-iquote ./include			\
			-iquote ../utility/include	\
			-iquote ../../libs/myteams	\
			-L../../libs/myteams		\

LDFLAGS	+=	--coverage -lcriterion

all:		$(NAME)

debug:		CFLAGS	+=	-g
debug:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) -O2 -o $(NAME) $(OBJ) -lmyteams -luuid

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)
			$(RM) $(T_NAME)

re:			fclean all

.PHONY:		all clean fclean re tests_run tclean
