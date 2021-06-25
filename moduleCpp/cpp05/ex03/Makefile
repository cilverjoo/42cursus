NAME = Bureaucrat
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./ --std=c++98

SRCS = ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp Bureaucrat.cpp Intern.cpp Form.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(FLAGS) -c -o $@ $<
	
all : $(NAME)

clean :
	rm -f $(OBJS)
	rm -f tree_shrubbery

fclean : clean
	rm -f $(NAME)

re : fclean all
