/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:28:40 by heryu             #+#    #+#             */
/*   Updated: 2021/02/21 16:30:29 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			make_clean_word(t_env *env_list, t_token *token)
{
	while (token && (token->type != END || token->type != PIPE))
	{
		if ((word_to_env_value(env_list, &token->word)) == ERROR)
			return (ERROR);
		if ((remove_quote_in_word(&token->word)) == ERROR)
			return (ERROR);
		toggle_negative_char(token->word);
		token = token->next;
	}
	return (SUCCESS);
}

void		reset_std_fd(t_shell *minishell)
{
	dup2(minishell->origin_std[READ], STDIN);
	dup2(minishell->origin_std[WRITE], STDOUT);
}

int			execute_builtin(t_shell *minishell, char *cmd)
{
	if (ft_strcmp("pwd", cmd) == 0)
		return (cmd_pwd(minishell));
	else if (ft_strcmp("env", cmd) == 0)
		return (cmd_env(minishell));
	else if (ft_strcmp("echo", cmd) == 0)
		return (cmd_echo(minishell->cmd));
	else if (ft_strcmp("cd", cmd) == 0)
		return (cmd_cd(minishell->cmd, minishell));
	else if (ft_strcmp("export", cmd) == 0)
		return (cmd_export(minishell->cmd, minishell, minishell->tokens));
	else if (ft_strcmp("unset", cmd) == 0)
		return (cmd_unset(minishell->cmd, minishell, minishell->tokens));
	else if (ft_strcmp("exit", cmd) == 0)
		return (cmd_exit(minishell->cmd, minishell, minishell->tokens));
	else
		return (-1);
}

int			execute(t_shell *minishell)
{
	t_token	*token;
	int		ret;

	token = minishell->tokens;
	while (token)
	{
		make_clean_word(minishell->env_list, token);
		if (get_prev_pipe(token))
			prev_pipe_redir(minishell->pio);
		if (get_next_pipe(token))
			next_pipe_redir(minishell->pio);
		if (set_redir(token) != ERROR)
		{
			make_cmd(minishell, token);
			if ((ret = execute_builtin(minishell, minishell->cmd[0])) < 0)
				execute_cmd(minishell, token);
		}
		clear_cmd(minishell, SUCCESS);
		reset_std_fd(minishell);
		token = get_next_run_token(token);
	}
	return (SUCCESS);
}
