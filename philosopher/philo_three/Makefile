NAME = philo_three
CC = gcc
CFLAGS = -g3 -fsanitize=address -Wall -Wextra -Werror -pthread -I./

SRCS =		main.c \
			init.c \
			utils.c \
			dining.c \
			monitor.c
			
OBJS =	$(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

all : $(NAME)

clean : 
	rm $(OBJS)

fclean :
	rm $(NAME)
	rm $(OBJS)

re : fclean all
