/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 01:38:07 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 16:36:14 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			sort_export_list(t_env **exp_head)
{
	t_env	*exp;
	t_env	*exp2;
	char	*key;
	char	*value;

	exp = *exp_head;
	while (exp)
	{
		exp2 = *exp_head;
		while (exp2->next)
		{
			if (ft_strcmp(exp2->key, exp2->next->key) > 0)
			{
				key = exp2->key;
				value = exp2->value;
				exp2->key = exp2->next->key;
				exp2->value = exp2->next->value;
				exp2->next->key = key;
				exp2->next->value = value;
			}
			exp2 = exp2->next;
		}
		exp = exp->next;
	}
	return (SUCCESS);
}

int			make_export_list(t_shell *minishell)
{
	t_env	*env_list;
	t_env	*new;
	t_env	*prev_node;

	env_list = minishell->env_list;
	prev_node = NULL;
	while (env_list)
	{
		if (!(new = new_env_node(env_list->key, env_list->value)))
			return (clear_env(minishell->export_list, ERROR));
		if (prev_node == NULL)
			minishell->export_list = new;
		else
			prev_node->next = new;
		new->next = NULL;
		prev_node = new;
		env_list = env_list->next;
	}
	sort_export_list(&minishell->export_list);
	return (SUCCESS);
}
