NAME = libasm.a
SRCS = ft_strlen.s ft_strcpy.s ft_strcmp.s \
		ft_read.s ft_write.s ft_strdup.s
OBJS = $(SRCS:.s=.o)

%.o		: %.s
	nasm -f macho64 $< -o $@

$(NAME)	: $(OBJS)
	ar rcs $(NAME) $(OBJS)

all		: $(NAME)

clean	:
	rm -rf $(OBJS)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all