SRCS = minimain.c helperfunctions/dblepoi.c helperfunctions/dblepoi2.c signals.c parse/parse.c parse/parse2.c parse/parsecomplete.c path.c builtinfuncs/cd.c\
		builtinfuncs/pwd.c builtinfuncs/env.c builtinfuncs/export.c helperfunctions/errorcontrol.c pipe.c execv.c builtinfuncs/unset.c builtinfuncs/exit.c inputandoutput/inputandoutput.c\
		dollar/dollar.c redirections.c helperfunctions/execute.c parse/parse3.c helperfunctions/executeforred.c helperfunctions/quotesfunctions.c helperfunctions/redfunctions.c\
		helperfunctions/shellinit.c helperfunctions/freevarforwhile.c builtinfuncs/echo.c parse/handle_parse.c

CC = @gcc
NAME = minishell
CFLAGS = -Wall -Wextra -Werror
RM = @rm -rf

READLINE = readline

all: $(READLINE) $(NAME)

$(READLINE):
	curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	tar -xvf readline-8.2.tar.gz
	cd readline-8.2 && ./configure --prefix=${PWD}/readline
	cd readline-8.2 && make install

$(NAME):
	make -C libft/
	$(CC) -o $(NAME) $(CFLAGS) -L${PWD}/readline/lib  -I${PWD}/readline/include/ -lreadline libft/libft.a $(SRCS)

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft/

clean:
	$(RM) readline-8.2 readline-8.2.tar.gz
	make clean -C libft/

re: fclean all
