/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:38:59 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 13:45:43 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_backslash_char_cnt(char *line)
{
	int		i;
	int		cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == '\\' && check_io_quote(line, i) == D_INNER)
		{
			if (line[i + 1] == '\\' || line[i + 1] == '`'
				|| line[i + 1] == '$' || line[i + 1] == '"')
			{
				cnt++;
				i++;
			}
		}
		i++;
	}
	return (cnt);
}

void	copy_except_backslash_char(char *line, char *new_line, int index)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && j < index)
	{
		if (line[i] == '\\' && check_io_quote(line, i) == D_INNER &&
			(line[i + 1] == '\\' || line[i + 1] == '`'
			|| line[i + 1] == '$' || line[i + 1] == '"'))
		{
			line[i + 1] = -(char)line[i + 1];
			i++;
		}
		new_line[j++] = line[i++];
	}
	new_line[j] = '\0';
}

int		remove_backslash_char(t_shell *minishell)
{
	int		i;
	int		cnt;
	char	*new_line;

	cnt = get_backslash_char_cnt(minishell->line);
	i = ft_strlen(minishell->line);
	while (is_space(minishell->line[--i]))
		;
	if ((new_line = (char *)malloc(sizeof(char) * (i + 1 - cnt + 1))) == 0)
		return (ERROR);
	copy_except_backslash_char(minishell->line, new_line, i + 1 - cnt);
	free(minishell->line);
	minishell->line = new_line;
	return (SUCCESS);
}

int		make_escape_env_char_negative(t_shell *minishell)
{
	int		i;
	char	*line;

	i = 0;
	line = minishell->line;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (check_io_quote(line, i) == S_INNER ||
				(i != 0 && line[i - 1] == '\\') ||
				line[i + 1] == ' ' || line[i + 1] == '\0')
			{
				line[i] = -(char)line[i];
			}
		}
		i++;
	}
	return (SUCCESS);
}

int		toggle_negative_char(char *word)
{
	int		i;

	i = 0;
	while (word[i])
	{
		if (word[i] < 0)
			word[i] = -(char)word[i];
		i++;
	}
	return (SUCCESS);
}
