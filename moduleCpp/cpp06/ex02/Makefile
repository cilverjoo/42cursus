NAME = generator
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./ -std=c++98

SRCS = A.cpp B.cpp C.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
