/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:20:50 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 14:21:04 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		set_input_redir(t_token *token)
{
	char	*file_name;
	int		fd;

	file_name = token->next->word;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERROR);
		ft_putstr_fd(file_name, STDERROR);
		ft_putstr_fd(": No such file or directory\n", STDERROR);
		g_minishell.exit_status = 1;
		return (ERROR);
	}
	dup2(fd, STDIN);
	close(fd);
	return (SUCCESS);
}

int		set_output_redir(t_token *token)
{
	char	*file_name;
	int		fd;

	file_name = token->next->word;
	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERROR);
		ft_putstr_fd(file_name, STDERROR);
		ft_putstr_fd(": TRUNC ERROR\n", STDERROR);
		return (ERROR);
	}
	dup2(fd, STDOUT);
	close(fd);
	return (SUCCESS);
}

int		set_add_redir(t_token *token)
{
	char	*file_name;
	int		fd;

	file_name = token->next->word;
	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERROR);
		ft_putstr_fd(file_name, STDERROR);
		ft_putstr_fd(": APPEND ERROR\n", STDERROR);
		return (ERROR);
	}
	dup2(fd, STDOUT);
	close(fd);
	return (SUCCESS);
}

int		set_redir(t_token *token)
{
	while (token && token->type != END && token->type != PIPE)
	{
		if (token->type == INPUT)
		{
			if (set_input_redir(token) == ERROR)
				return (ERROR);
		}
		if (token->type == OUTPUT)
		{
			if (set_output_redir(token) == ERROR)
				return (ERROR);
		}
		if (token->type == ADD)
		{
			if (set_add_redir(token) == ERROR)
				return (ERROR);
		}
		token = token->next;
	}
	return (SUCCESS);
}
