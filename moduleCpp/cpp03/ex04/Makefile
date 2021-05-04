NAME = trap
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./

SRCS = SuperTrap.cpp NinjaTrap.cpp FragTrap.cpp ScavTrap.cpp ClapTrap.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
