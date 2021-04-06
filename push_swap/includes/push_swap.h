/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 16:04:52 by ekim              #+#    #+#             */
/*   Updated: 2021/03/24 17:41:21 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "../lib/libft.h"
# include "../lib/get_next_line.h"

typedef struct		s_instr
{
	char			*content;
	struct s_instr	*next;
}					t_instr;

typedef struct		s_ps
{
	int				size;
	int				*sorted_array;
	t_list			*stack_a;
	t_list			*stack_b;
	t_instr			*instr;
	t_instr			*p_instr;
}					t_ps;

int					exit_program(void);
t_ps				*init_ps(int size);

int					check_valid_arg(char *str, int *ptr);
int					make_stack_list(char **av, t_ps *ps);
void				read_instruction(t_ps *ps);
int					execute_instr(t_ps *ps, char *content);
int					execute_instrs(t_ps *ps);
int					check_instr_valid(char *instr);
int					check_stack_is_sorted(t_list *stack);
int					check_is_ok(t_ps *ps, int check);
int					check_double(t_ps *ps);
int					get_chunk_size(t_ps *ps);

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

int					do_sorting(t_ps *ps);
void				move_to_a_in_sequence(t_ps *ps, int idx1, int idx2);
void				show_stacks(t_ps *ps);

void				make_sorted_array(int *array, t_ps *ps);
void				sort_small_list(t_ps *ps);
void				get_arg_and_push_to_b(t_ps *ps, int depth);
void				get_arg_and_push_to_a(t_ps *ps, int depth);
void				sort_args_small_than_chunk(t_ps *ps, int idx1, int idx2);

#endif
