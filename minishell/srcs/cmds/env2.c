/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:53:35 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 16:34:52 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			add_new_env(t_env *list, char *key, char *value)
{
	t_env	*env;
	t_env	*new;

	new = new_env_node(key, value);
	env = list;
	while (env)
	{
		if (env->next == NULL)
		{
			env->next = new;
			break ;
		}
		env = env->next;
	}
	return (SUCCESS);
}

int			replace_env_node(t_env *list, char *key, char *value)
{
	t_env	*env;
	char	*tmp;

	env = list;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			tmp = env->value;
			env->value = value;
			free(tmp);
			return (SUCCESS);
		}
		env = env->next;
	}
	add_new_env(list, key, value);
	free(value);
	return (SUCCESS);
}

int			check_existing_key(t_env *list, char *key)
{
	while (list)
	{
		if (ft_strcmp(list->key, key) == 0)
			return (1);
		list = list->next;
	}
	return (0);
}

int			cmd_env(t_shell *minishell)
{
	t_env	*env;

	env = minishell->env_list;
	while (env)
	{
		ft_putstr_fd(env->key, STDOUT);
		ft_putstr_fd("=", STDOUT);
		ft_putstr_fd(env->value, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		env = env->next;
	}
	ft_putstr_fd("_=/usr/bin/env\n", STDOUT);
	minishell->exit_status = 0;
	return (SUCCESS);
}
