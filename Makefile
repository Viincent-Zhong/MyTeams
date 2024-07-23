##
## EPITECH PROJECT, 2022
## Project myteams
## File description:
## main Makefile
##

SERVER		=	src/server/

CLI			=	src/client/

EXEC_SERVER	=	myteams_server

EXEC_CLI	=	myteams_cli

all:
				make -C $(SERVER)
				mv $(SERVER)$(EXEC_SERVER) .
				make -C $(CLI)
				mv $(CLI)$(EXEC_CLI) .

server:
				make -C $(SERVER)

cli:
				make -C $(CLI)

debug:
				make -C $(SERVER) debug
				mv $(SERVER)$(EXEC_SERVER) .
				make -C $(CLI) debug
				mv $(CLI)$(EXEC_CLI) .

clean:
				make -C $(SERVER) clean
				make -C $(CLI) clean

fclean:			clean
				$(RM) $(EXEC_SERVER)
				$(RM) $(EXEC_CLI)
				make -C $(SERVER) fclean
				make -C $(CLI) fclean

tclean:			clean
				make -C tests/ tclean

re:				fclean all

rdebug:			fclean debug

tests_run:
				make -C tests/ tests_run

.PHONY:			all clean fclean re tests_run server cli rdebug tclean
