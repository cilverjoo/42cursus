NAME = Intern
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./

SRCS = ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp Bureaucrat.cpp Intern.cpp Form.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

all : $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
