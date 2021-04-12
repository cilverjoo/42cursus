NAME = philo_one
CC = gcc
<<<<<<< HEAD
CFLAGS = -Wall -Wextra -Werror -I./
=======
CFLAGS = -Wall -Wextra -Werror -pthread -I./
>>>>>>> main
SRCS =		main.c \
			init.c \
			utils.c \
			dining.c \
			monitor.c

OBJS =	$(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -pthread

all : $(NAME)

clean : 
	rm $(OBJS)

fclean : clean
	rm $(NAME)

re : fclean all
