#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct		s_ps
{
	int 			len;
	t_list			*stack_a;
	t_list			*stack_b;
	t_list			*instr;
}					t_ps;

#endif