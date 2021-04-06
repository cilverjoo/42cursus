/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:26:53 by heryu             #+#    #+#             */
/*   Updated: 2021/02/21 14:32:46 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_space(char ch)
{
	if (ch == '\t' || ch == '\n' || ch == '\v' ||
		ch == '\f' || ch == '\r' || ch == ' ')
	{
		return (TRUE);
	}
	else
		return (FALSE);
}

int		is_sep(char ch)
{
	if (ch == '<' || ch == '>' || ch == ';' || ch == '|')
		return (TRUE);
	else
		return (FALSE);
}

int		skip_space(char *line, int *i)
{
	while (is_space(line[*i]))
		(*i)++;
	return (1);
}

void	free_ppmem(char **pp)
{
	int		i;

	if (pp == NULL)
		return ;
	i = 0;
	while (pp[i])
	{
		free(pp[i]);
		i++;
	}
	free(pp);
}

char	*get_value_from_key(t_shell *minishell, char *key)
{
	t_env	*env;

	env = minishell->env_list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (ERROR);
}
