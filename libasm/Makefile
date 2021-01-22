NAME = libasm.a
SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s \
		ft_read.s ft_write.s ft_strdup.s
OBJS = $(SRCS:.s=.o)

%.o		: %.s
	nasm -f elf64 $<
# nasm -f macho64 $< -o $@

all		: $(NAME)

$(NAME)	: $(OBJS)
	ar rcs $@ $^

test	: re
	gcc -o test -L. -lasm main.c
	./test
	rm test

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all

.PHONY:	clean fclean re test
