NAME = megaphone
CC = clang++
FLAGS = -Wall -Wextra -Werror

SRCS = megaphone.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@
	
all : $(NAME)

clean :
	rm $(OBJS)
	
fclean: clean
	rm $(NAME)
	
re: fclean re
