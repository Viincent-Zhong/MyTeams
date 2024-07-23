##
## EPITECH PROJECT, 2022
## Project myteams
## File description:
## Makefile for unit_test
##

T_NAME		=	unit_test

SRC_SERVER	=	../src/server/src/server.c						\
				../src/server/src/connection.c					\
				../src/server/src/handle_client.c				\
				../src/server/src/command.c						\
				../src/server/src/command/create_channel.c		\
				../src/server/src/command/create_comment.c		\
				../src/server/src/command/create_team.c			\
				../src/server/src/command/create_thread.c		\
				../src/server/src/command/joining_team.c		\
				../src/server/src/command/leaving_team.c		\
				../src/server/src/command/restore_conversation.c\
				../src/server/src/command/restore_data.c		\
				../src/server/src/command/save_conversation.c	\
				../src/server/src/command/save_data.c			\
				../src/server/src/command/login_user.c			\
				../src/server/src/command/logout_user.c			\
				../src/server/src/command/info_user.c			\
				../src/server/src/command/info_team.c			\
				../src/server/src/command/info_thread.c			\
				../src/server/src/command/info_channel.c		\
				../src/server/src/command/list_users.c			\
				../src/server/src/parser.c						\
				../src/server/src/parse/parse_channels.c		\
				../src/server/src/parse/parse_conversations.c	\
				../src/server/src/parse/parse_messages.c		\
				../src/server/src/parse/parse_teams.c			\
				../src/server/src/parse/parse_texts.c			\
				../src/server/src/parse/parse_threads.c			\
				../src/server/src/parse/parse_users.c			\
				../src/server/src/save.c						\
				../src/server/src/save/save_channels.c			\
				../src/server/src/save/save_conversations.c		\
				../src/server/src/save/save_messages.c			\
				../src/server/src/save/save_teams.c				\
				../src/server/src/save/save_texts.c				\
				../src/server/src/save/save_threads.c			\
				../src/server/src/save/save_users.c				\
				../src/server/src/free_server.c					\
				../src/utility/src/socket.c						\
				../src/utility/src/lib.c						\
				../src/utility/src/split_command.c				\
				../src/utility/src/read.c						\
				../src/server/src/deal_user.c					\
				../src/server/src/free/free_private.c			\
				../src/server/src/free/free_public.c			\
				../src/server/src/deal_teams.c					\
				../src/server/src/deal_channel.c					\
				../src/server/src/deal_thread.c					\
				../src/server/src/deal_reply.c					\
				../src/server/src/deal_users.c					\

SRC_CLI		=	../src/client/src/client.c						\
				../src/client/src/init.c						\
				../src/client/src/command/help.c				\
				../src/client/src/command/login.c				\
				../src/client/src/command/logout.c				\
				../src/client/src/command/users.c				\
				../src/client/src/command/user.c				\
				../src/client/src/command/send.c				\
				../src/client/src/command/messages.c			\
				../src/client/src/command/subscribe.c			\
				../src/client/src/command/subscribed.c			\
				../src/client/src/command/unsubscribe.c			\
				../src/client/src/command/use.c					\
				../src/client/src/command/create.c				\
				../src/client/src/command/list.c				\
				../src/client/src/command/info.c				\
				../src/client/src/command/unknow.c				\
				../src/client/src/get_command.c					\
				../src/client/src/server_announce.c				\
				../src/client/src/norm_announce.c				\

T_SRC		=	unit_test_server.c								\
				unit_test_parse.c								\
				unit_test_client.c								\
				$(SRC_SERVER)									\
				$(SRC_CLI)										\

CFLAGS		=	-iquote ./include								\
				-iquote ../utility/include						\
				-iquote ../../libs/myteams						\
				-iquote ../src/utility/include					\
				-iquote ../src/server/include					\
				-iquote ../src/client/include					\
				-iquote ../libs/myteams							\
				-L../libs/myteams								\

LDFLAGS		+=	--coverage -lcriterion

tests_run:		$(T_SRC)
				$(CC) $(CFLAGS) -o $(T_NAME) $(T_SRC) $(LDFLAGS) -lmyteams -luuid
				./$(T_NAME)
				gcovr

tclean:
				$(RM) *.gcno
				$(RM) *.gcda
