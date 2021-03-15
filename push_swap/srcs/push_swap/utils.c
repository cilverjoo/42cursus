#include "../../includes/push_swap.h"

void		init_stack(t_ps *ps)
{
	ps->stack_a = ft_lstnew(NULL);
	ps->stack_b = ft_lstnew(NULL);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int			exit_program(void)
{
	char	*error;

	error = "Error\n";
	write(2, error, 6);
	exit(0);
}