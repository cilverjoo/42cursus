/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:15:28 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 13:27:16 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_valid_quote(t_shell *minishell)
{
	char	*line;
	size_t	line_length;
	int		last_status;

	line = minishell->line;
	line_length = ft_strlen(line);
	if (line_length == 0)
		return (VALID);
	last_status = check_io_quote(line, line_length - 1);
	if (last_status == S_INNER || last_status == D_INNER)
		return (INVALID);
	return (VALID);
}

int		is_valid_ascii(t_shell *minishell)
{
	size_t	i;
	char	*line;

	line = minishell->line;
	i = 0;
	while (line[i])
	{
		if (!ft_isascii(line[i]))
			return (INVALID);
		i++;
	}
	return (VALID);
}

int		is_valid_escape(t_shell *minishell)
{
	size_t	i;
	char	*line;

	i = 0;
	line = minishell->line;
	while (line[i])
	{
		if (line[i] == '\\' && check_io_quote(line, i) % 2 != 0)
		{
			return (INVALID);
		}
		i++;
	}
	return (VALID);
}

int		is_valid_token_type(t_token *token)
{
	while (token)
	{
		if (token->type >= INPUT)
		{
			if (!token->next || token->next->type != FILE)
				return (INVALID);
			if (!get_prev_cmd(token) && !get_next_cmd(token))
				return (INVALID);
		}
		if (token->type == END
				&& (!get_prev_cmd(token)))
			return (INVALID);
		if (token->type == PIPE
				&& (!get_prev_cmd(token) || !get_next_cmd(token)))
			return (INVALID);
		token = token->next;
	}
	return (VALID);
}
