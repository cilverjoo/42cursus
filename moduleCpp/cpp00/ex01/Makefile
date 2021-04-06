NAME = phonebook
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./

SRCS =	main.cpp \
	show.cpp \
	set_phonebook.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) -o $(NAME)

all : $(NAME)

clean :
	rm $(OBJS)

fclean : clean
	rm $(NAME)

re : fclean all 
