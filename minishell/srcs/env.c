/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:37:52 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 15:58:40 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env		*new_env_node(char *key, char *value)
{
	t_env	*env;

	if ((env = ft_calloc(1, sizeof(t_env))) == NULL)
		return (NULL);
	env->key = ft_strdup(key);
	if (value)
		env->value = ft_strdup(value);
	else
		env->value = ft_strdup("NULL");
	return (env);
}

t_env		*allocate_new_env
(
	t_shell *minishell,
	char **tmp,
	t_env *prev,
	t_env *new)
{
	if (prev == NULL)
		minishell->env_list = new;
	else
		prev->next = new;
	new->next = NULL;
	if (ft_strcmp(tmp[0], "HOME") == 0)
		minishell->home_dir = ft_strdup(tmp[1]);
	else if (ft_strcmp(tmp[0], "OLDPWD") == 0)
		minishell->old_dir = ft_strdup(tmp[1]);
	return (new);
}

int			init_env(t_shell *minishell, char **envp)
{
	int		i;
	char	**tmp;
	t_env	*new_node;
	t_env	*prev_node;

	i = -1;
	prev_node = NULL;
	while (envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		if (ft_strcmp(tmp[0], "_") == 0)
		{
			free_ppmem(tmp);
			continue ;
		}
		if ((new_node = new_env_node(tmp[0], tmp[1])) == NULL)
		{
			free_ppmem(tmp);
			return (clear_env(minishell->env_list, ERROR));
		}
		prev_node = allocate_new_env(minishell, tmp, prev_node, new_node);
		free_ppmem(tmp);
	}
	return (SUCCESS);
}
