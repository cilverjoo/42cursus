# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 13:53:51 by ekim              #+#    #+#              #
#    Updated: 2021/04/07 17:58:37 by ekim             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = phonebook
CC = clang++
FLAGS = -Wall -Wextra -Werror -I./

SRCS =	main.cpp \
		contact.cpp \
		phonebook.cpp

OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

all : $(NAME)

clean :
	rm $(OBJS)

fclean : clean
	rm $(NAME)

re : fclean all 
