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
	int 			size;
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
int					check_is_ok(t_ps *ps, int check);

//instructions
t_instr				*new_instr_node(char *instr);
void				instr_add_back(t_instr **lst, t_instr *new);
int					push_a(t_list **stack_a, t_list **stack_b, int check);
int					push_b(t_list **stack_a, t_list **stack_b, int check);
int					reverse_a(t_list **stack, int check);
int					reverse_b(t_list **stack, int check);
int					reverse_both(t_ps *ps, int check);
int					rotate_a(t_list **stack, int check);
int					rotate_b(t_list **stack, int check);
int					rotate_both(t_ps *ps, int check);
int					swap_a(t_list *stack, int check);
int					swap_b(t_list *stack, int check);
int					swap_both(t_ps *ps, int check);

//push swap
int					do_sorting(t_ps *ps);
void				merge_sort(int chunk_size, t_ps *ps);
void				move_chunk_to_b_and_reverse(int chunk_size, t_ps *ps);
void				rotate_remains(int remains, t_ps *ps);
void				show_stacks(t_ps *ps);

int					*make_sorted_array(t_ps *ps);
void				sort_small_list(t_ps *ps);
void				simple_sort(t_ps *ps, int *arr, int pivot);

#endif