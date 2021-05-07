NAME = marine
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./

SRCS = AssaultTerminator.cpp Squad.cpp TacticalMarine.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
