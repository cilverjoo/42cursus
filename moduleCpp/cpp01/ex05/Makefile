NAME = human
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./

SRCS = Human.cpp Brain.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

all : $(NAME)

clean :
	rm $(OBJS)

fclean : clean
	rm $(NAME)

re : fclean all
