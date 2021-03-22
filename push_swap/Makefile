CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -I./includes  # CFLAGS = -Wall -Wextra -Werror -fsanitize=address -I./includes
CHECKER = checker
PUSHSWAP = push_swap

LIB_DIR = ./lib
LIB_NAME = ft		#library 이름은 lib와 .a 사이의 이름이다. libft.a ==> ft

SRCS_DIR = ./srcs/

CHECKER_NAME =	checker/checker.c \
				utils.c \
				push.c \
				reverse.c \
				swap.c \
				rotate.c \
				instructions.c \
				check.c \
				stack.c \
				simple_sort.c \
				sort.c

PUSHSWAP_NAME =	push_swap/push_swap.c \
				utils.c \
				push.c \
				reverse.c \
				swap.c \
				rotate.c \
				instructions.c \
				check.c \
				stack.c \
				simple_sort.c \
				sort.c
				
CHECKER_SRCS = $(addprefix $(SRCS_DIR), $(CHECKER_NAME))
PUSHSWAP_SRCS = $(addprefix $(SRCS_DIR), $(PUSHSWAP_NAME))

C_OBJS = $(CHECKER_SRCS:.c=.o)
P_OBJS = $(PUSHSWAP_SRCS:.c=.o)

$(CHECKER) : $(C_OBJS)
	$(MAKE) -C $(LIB_DIR) bonus
	$(CC) $(CFLAGS) -L$(LIB_DIR) -l$(LIB_NAME) $^ -o $@

$(PUSHSWAP) : $(P_OBJS)
	$(MAKE) -C $(LIB_DIR) bonus
	$(CC) $(CFLAGS) -L$(LIB_DIR) -l$(LIB_NAME) $^ -o $@

all : $(CHECKER) $(PUSHSWAP)

clean :
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(C_OBJS) $(P_OBJS)

fclean : clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -rf $(CHECKER) $(PUSHSWAP)

re : fclean all
