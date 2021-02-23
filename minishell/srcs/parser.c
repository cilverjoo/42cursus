/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 16:37:52 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/18 15:32:11 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		read_line(t_shell *minishell)
{
	char	*line;

	while (!get_next_line(STDIN, &line))
	{
		minishell->line = ft_strjoin_free(minishell->line, line, TRUE, TRUE);
		if (minishell->line[0] == '\0')
		{
			ft_putstr_fd("exit\n", STDOUT);
			clear_all(minishell, SUCCESS, TRUE);
			exit(0);
		}
		ft_putstr_fd("  \b\b", STDOUT);
	}
	minishell->line = ft_strjoin_free(minishell->line, line, TRUE, TRUE);
	if (minishell->line[0] == '\0')
		minishell->exit_status = 0;
	return (SUCCESS);
}

int		make_space_sep_line(t_shell *minishell)
{
	int		size;
	char	*new_line;

	size = get_space_sep_line_size(minishell->line);
	if ((new_line = (char *)malloc(sizeof(char) * (size + 1))) == NULL)
		return (ERROR);
	copy_space_sep_line(minishell->line, new_line, 0, 0);
	free(minishell->line);
	minishell->line = new_line;
	return (SUCCESS);
}

int		make_token(t_shell *minishell)
{
	int		i;

	i = 0;
	while (minishell->line[i])
	{
		if (!is_space(minishell->line[i]))
		{
			if ((make_a_token(minishell, &i)) == ERROR)
				return (ERROR);
			continue;
		}
		i++;
	}
	specify_token_type(minishell->tokens);
	return (SUCCESS);
}

int		parsing(t_shell *minishell)
{
	read_line(minishell);
	if (!is_valid_ascii(minishell) || !is_valid_quote(minishell) ||
		!is_valid_escape(minishell))
	{
		ft_putstr_fd("minishell: syntax error\n", STDERROR);
		minishell->exit_status = 258;
		return (ERROR);
	}
	make_space_sep_line(minishell);
	remove_backslash_char(minishell);
	make_escape_env_char_negative(minishell);
	make_token(minishell);
	if (!is_valid_token_type(minishell->tokens))
	{
		ft_putstr_fd("minishell: syntax error\n", STDERROR);
		minishell->exit_status = 258;
		return (ERROR);
	}
	return (SUCCESS);
}
