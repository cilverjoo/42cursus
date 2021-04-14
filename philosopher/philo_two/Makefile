NAME = philo_two
CC = gcc
FLAGS = -Wall -Wextra -Werror -I./

SRCS = main.c \
		utils.c \
		monitor.c \
		init.c \
		dining.c

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@ 

all : $(NAME)

clean :
	rm $(OBJS)

fclean : clean
	rm $(NAME)

re : fclean all
