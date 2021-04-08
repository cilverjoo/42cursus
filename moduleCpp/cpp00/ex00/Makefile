# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 13:54:47 by ekim              #+#    #+#              #
#    Updated: 2021/04/07 18:03:49 by ekim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = megaphone

SRCS = main.cpp

CC = clang++

FLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@
	
all : $(NAME)

clean :
	rm $(OBJS)
	
fclean: clean
	rm $(NAME)

re: fclean all
