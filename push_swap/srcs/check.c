/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekim <ekim@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 16:10:40 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/03/22 12:50:10 by ekim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int			check_instr_valid(char *instr)
{
	if (ft_strncmp(instr, "sa", 2) == 0 || ft_strncmp(instr, "sb", 2) == 0
		|| ft_strncmp(instr, "ss", 2) == 0 || ft_strncmp(instr, "pa", 2) == 0
		|| ft_strncmp(instr, "pb", 2) == 0 || ft_strncmp(instr, "ra", 2) == 0
		|| ft_strncmp(instr, "rb", 2) == 0 || ft_strncmp(instr, "rr", 2) == 0
		|| ft_strncmp(instr, "rra", 3) == 0 || ft_strncmp(instr, "rrb", 3) == 0
		|| ft_strncmp(instr, "rrr", 3) == 0)
		return (1);
	return (0);
}

int			check_arg_has_flag(char c, int *minus)
{
	if (c == '-' || c == '+')
	{
		if (c == '-')
			*minus = -1;
		return (1);
	}
	return (0);
}

int			check_valid_arg(char *str, int *ptr)
{
	long	ret;
	int		len;
	int		minus;
	int		i;
	int		num;

	i = 0;
	minus = 1;
	len = (int)ft_strlen(str);
	i += check_arg_has_flag(str[i], &minus);
	ret = 0;
	while (i < len)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	if (ret > 2147483647 || ret * minus < -2147483648)
		return (0);
	num = (int)(ret * minus);
	*ptr = num;
	return (1);
}

int			check_is_ok(t_ps *ps, int check)
{
	if (ps->stack_b || !check_stack_is_sorted(ps->stack_a))
	{
		if (check == 1)
			write(1, "KO\n", 3);
		return (0);
	}
	if (check == 1)
		write(1, "OK\n", 3);
	return (1);
}
