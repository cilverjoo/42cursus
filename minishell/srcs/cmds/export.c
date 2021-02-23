/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 19:27:02 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 16:37:35 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			show_export_list(t_shell *minishell)
{
	t_env	*exp;

	exp = minishell->export_list;
	while (exp)
	{
		if (ft_strcmp(exp->value, "NULL") == 0)
		{
			ft_putstr_fd("declare -x ", STDOUT);
			ft_putstr_fd(exp->key, STDOUT);
			ft_putstr_fd("\n", STDOUT);
		}
		else
		{
			ft_putstr_fd("declare -x ", STDOUT);
			ft_putstr_fd(exp->key, STDOUT);
			ft_putstr_fd("=\"", STDOUT);
			ft_putstr_fd(exp->value, STDOUT);
			ft_putstr_fd("\"\n", STDOUT);
		}
		exp = exp->next;
	}
	minishell->exit_status = 0;
	return (SUCCESS);
}

int			check_valid_key(char *cmd)
{
	int		i;
	int		j;
	int		check;

	i = -1;
	check = 0;
	while (cmd[++i])
		if (cmd[i] == '=')
		{
			check = 1;
			break ;
		}
	if (ft_isdigit(cmd[0]) || (i == 0 && check == 1))
		return (-2);
	j = 0;
	while (j < i)
	{
		if (!ft_isalnum(cmd[j]))
			return (-2);
		j++;
	}
	if (check == 0)
		return (-1);
	return (SUCCESS);
}

int			export_exceptions(t_shell *minishell, int exp_option, char *cmd)
{
	char	**splited;

	if (exp_option == -1)
	{
		if (!check_existing_key(minishell->export_list, cmd))
			add_new_env(minishell->export_list, cmd, NULL);
	}
	else if (exp_option == -2)
	{
		splited = ft_split(cmd, '=');
		ft_putstr_fd("minishell: export: '", STDERROR);
		if (cmd[0] != '=')
			ft_putstr_fd(splited[0], STDERROR);
		else
			ft_putstr_fd(cmd, STDERROR);
		ft_putstr_fd("': not a valid identifier\n", STDERROR);
		minishell->exit_status = 1;
		free_ppmem(splited);
		return (ERROR);
	}
	return (SUCCESS);
}

int			cmd_export(char **cmd, t_shell *mini, t_token *token)
{
	int		i;
	int		op;
	char	**split;

	if (!cmd[1])
		return (show_export_list(mini));
	i = 1;
	while (cmd[i])
	{
		if (((op = check_valid_key(cmd[i])) < 0) &&
			!export_exceptions(mini, op, cmd[i]))
			return (ERROR);
		else if (op > 0 && !get_next_pipe(token) && !get_prev_pipe(token))
		{
			split = ft_split(cmd[i], '=');
			replace_env_node(mini->env_list, split[0], ft_strdup(split[1]));
			replace_env_node(mini->export_list, split[0], ft_strdup(split[1]));
			free_ppmem(split);
		}
		i++;
	}
	mini->exit_status = 0;
	return (SUCCESS);
}
