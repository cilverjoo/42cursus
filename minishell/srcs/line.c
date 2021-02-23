/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:32:18 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 13:38:19 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_space_sep_line_size(char *line)
{
	int		i;
	int		ret_size;

	i = 0;
	ret_size = 0;
	skip_space(line, &i);
	while (line[i])
	{
		if (is_space(line[i]) && check_io_quote(line, i) % 2 != 0)
			ret_size += skip_space(line, &i);
		if (line[i] == '\0')
			break ;
		if (is_sep(line[i]) && check_io_quote(line, i) % 2 != 0)
		{
			if (i != 0 && !is_space(line[i - 1]))
				ret_size++;
			if (ft_strncmp(line + i, ">>", 2) == 0 && ++i)
				ret_size++;
			if (!is_space(line[i + 1]))
				ret_size++;
		}
		ret_size++;
		i++;
	}
	return (ret_size);
}

void	copy_space_sep_line(char *line, char *new_line, int i, int j)
{
	skip_space(line, &i);
	while (line[i])
	{
		if (is_space(line[i]) && check_io_quote(line, i) % 2 != 0)
		{
			new_line[j++] = ' ';
			skip_space(line, &i);
			continue;
		}
		if (is_sep(line[i]) && check_io_quote(line, i) % 2 != 0)
		{
			if (i != 0 && !is_space(line[i - 1]))
				new_line[j++] = ' ';
			new_line[j++] = line[i];
			if (ft_strncmp(line + i, ">>", 2) == 0 && ++i)
				new_line[j++] = '>';
			if (!is_space(line[i + 1]))
				new_line[j++] = ' ';
		}
		else
			new_line[j++] = line[i];
		i++;
	}
	new_line[j] = '\0';
}
