NAME = libft.a
CC = gcc
AFLAGS = rcs
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_isdigit.c ft_strlen.c ft_strncmp.c get_next_line.c get_next_line_utils.c

BONUS = ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
			ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJECTS = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS:.c=.o)

all : $(NAME)

clean :
	rm -rf $(OBJECTS) $(BONUS_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

bonus : $(OBJECTS) $(BONUS_OBJS)
	ar $(AFLAGS) $(NAME) $(OBJECTS) $(BONUS_OBJS)

$(NAME) : $(OBJECTS)
	ar $(AFLAGS) $(NAME) $(OBJECTS)
	
.PHONY : all clean fclean re bonus%
