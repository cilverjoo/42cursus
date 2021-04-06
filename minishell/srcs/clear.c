/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:37:40 by heryu             #+#    #+#             */
/*   Updated: 2021/02/21 13:02:17 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int				clear_env(t_env *list, int ret)
{
	t_env		*cur_node;
	t_env		*free_node;

	cur_node = list;
	while (cur_node)
	{
		free(cur_node->key);
		free(cur_node->value);
		free_node = cur_node;
		cur_node = cur_node->next;
		free(free_node);
	}
	list = NULL;
	return (ret);
}

int				clear_line(t_shell *minishell, int ret)
{
	free(minishell->line);
	minishell->line = NULL;
	return (ret);
}

int				clear_tokens(t_shell *minishell, int ret)
{
	t_token		*cur_node;
	t_token		*free_node;

	cur_node = minishell->tokens;
	while (cur_node)
	{
		free(cur_node->word);
		free_node = cur_node;
		cur_node = cur_node->next;
		free(free_node);
	}
	minishell->tokens = NULL;
	return (ret);
}

int				clear_cmd(t_shell *minishell, int ret)
{
	int			i;

	i = 0;
	if (!minishell->cmd)
		return (ret);
	while (minishell->cmd[i])
	{
		free(minishell->cmd[i]);
		i++;
	}
	free(minishell->cmd);
	minishell->cmd = NULL;
	return (ret);
}

int				clear_all(t_shell *minishell, int status, int is_exit)
{
	if (is_exit)
	{
		clear_env(minishell->export_list, status);
		clear_env(minishell->env_list, status);
		free(minishell->home_dir);
		free(minishell->cur_dir);
		free(minishell->old_dir);
	}
	clear_line(minishell, status);
	clear_tokens(minishell, status);
	clear_cmd(minishell, status);
	return (status);
}
