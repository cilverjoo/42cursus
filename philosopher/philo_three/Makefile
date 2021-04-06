NAME = philo_three
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I./

SRCS =		main.c \
			init.c \
			utils.c \
			dining.c \
			monitor.c
			
OBJS =	$(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread

all : $(NAME)

clean : 
	rm $(OBJS)

fclean : clean
	rm $(NAME)

re : fclean all
