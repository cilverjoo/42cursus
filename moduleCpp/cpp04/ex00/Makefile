NAME = Sorcerer
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./

SRCS = Sorcerer.cpp Victim.cpp Peon.cpp Peon2.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
