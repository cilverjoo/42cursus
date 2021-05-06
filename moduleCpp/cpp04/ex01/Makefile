NAME = Character
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./

SRCS = AWeapon.cpp PlasmaRifle.cpp PowerFist.cpp Enemy.cpp RadScorpion.cpp \
		SuperMutant.cpp Character.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
