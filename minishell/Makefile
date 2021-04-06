CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./includes

NAME = minishell

LIB_DIR = ./lib
LIB_NAME = ft

SRCS_DIR = ./srcs
SRCS_NAME = main.c \
			env.c \
			escape.c \
			clear.c \
			parser.c \
			exec.c \
			line.c \
			quote.c \
			signal.c \
			token.c \
			valid.c \
			get_env.c \
			get_token.c \
			pipe.c \
			redir.c \
			replace_env.c \
			utils.c \
			exec_cmd.c \
			cmds/cd.c \
			cmds/echo.c \
			cmds/env2.c \
			cmds/export.c \
			cmds/export2.c \
			cmds/unset.c \
			cmds/exit.c \
			cmds/pwd.c

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(MAKE) -C $(LIB_DIR) bonus
	$(CC) $(CFLAGS) -L$(LIB_DIR) -l$(LIB_NAME) $^ -o $@

$(SRCS_DIR)/%.o : %(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

clean :
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJS)

fclean : clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -rf $(NAME)

re : fclean all

t : all clean
	./minishell
