/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:22:10 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 16:36:27 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			unset_this_env(t_env *list, char *key)
{
	t_env	*env;
	t_env	*prev;

	env = list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->key);
			free(env->value);
			prev->next = env->next;
			free(env);
			env = NULL;
			return (SUCCESS);
		}
		prev = env;
		env = env->next;
	}
	return (ERROR);
}

int			unset_valid_check(char *cmd, t_shell *minishell)
{
	int		valid_check;
	int		i;

	valid_check = 1;
	i = -1;
	while (cmd[++i])
		if (!ft_isalnum(cmd[i]))
			valid_check = 0;
	if (ft_isdigit(*cmd) || valid_check == 0)
	{
		ft_putstr_fd("minishell: unset: '", STDERROR);
		ft_putstr_fd(cmd, STDERROR);
		ft_putstr_fd("': not a valid identifier\n", STDERROR);
		minishell->exit_status = 1;
		return (ERROR);
	}
	return (SUCCESS);
}

int			cmd_unset(char **cmd, t_shell *minishell, t_token *token)
{
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (!unset_valid_check(cmd[i], minishell))
			return (ERROR);
		if (!get_next_pipe(token) && !get_prev_pipe(token))
		{
			unset_this_env(minishell->env_list, cmd[i]);
			unset_this_env(minishell->export_list, cmd[i]);
		}
	}
	minishell->exit_status = 0;
	return (SUCCESS);
}
