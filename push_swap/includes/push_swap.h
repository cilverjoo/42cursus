#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "../lib/libft.h"
# include "../lib/get_next_line.h"

typedef struct      s_instr
{
	char 			*content;
	struct s_instr	*next;
}					t_instr;

typedef struct		s_ps
{
	int 			len;
	int				is_sorted;
	t_list			*stack_a;
	t_list			*stack_b;
	t_instr			*instr;
	t_instr			*p_instr;
}					t_ps;

//utils
int					exit_program(void);
t_ps				*init_ps(void);

//checker
int					check_valid_arg(char *str, int *ptr);
int					make_stack_list(char **av, t_ps *ps);
void				read_instruction(t_ps *ps);
int					execute_instr(t_ps *ps);
int 				check_instr_valid(char *instr);
int					check_stack_is_sorted(t_list *stack);
int					check_is_ok(t_ps *ps);

//instructions
t_instr				*new_instr_node(char *instr);
int					push(t_list **stack_a, t_list **stack_b);
int					reverse(t_list **stack);
int					reverse_both(t_ps *ps);
int					rotate(t_list **stack);
int					rotate_both(t_ps *ps);
int					swap(t_list *stack);
int					swap_both(t_ps *ps);

//push swap


#endif