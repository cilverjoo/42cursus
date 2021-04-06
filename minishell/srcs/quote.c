/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:29:08 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 13:30:16 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_escape_quote(char *line, int index)
{
	int		i;

	i = 0;
	while (line[i] && i < index)
	{
		if (line[i] == '\\')
		{
			if (line[i + 1] == '"' || line[i + 1] == '\\'
				|| line[i + 1] == '$' || line[i + 1] == '`')
			{
				if (i + 1 == index && line[i + 1] == '"')
					return (TRUE);
				i++;
			}
		}
		i++;
	}
	return (FALSE);
}

int		check_io_quote(char *line, size_t index)
{
	size_t	i;
	int		cur_status;

	if (ft_strlen(line) <= index)
		return (INVALID);
	cur_status = NO_QUOTE;
	i = 0;
	while (i <= index)
	{
		if (line[i] == '\"' && cur_status == D_INNER &&
			i != 0 && line[i - 1] == '\\' && is_escape_quote(line, i))
			;
		else if (line[i] == '\'' && cur_status != D_INNER)
			cur_status = (cur_status == S_INNER) ? S_OUTER : S_INNER;
		else if (line[i] == '\"' && cur_status != S_INNER)
			cur_status = (cur_status == D_INNER) ? D_OUTER : D_INNER;
		i++;
	}
	return (cur_status);
}

int		remove_quote_in_word(char **word)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strlen(*word) + 1));
	if (tmp == NULL)
		return (ERROR);
	copy_word_except_quote(tmp, *word);
	free(*word);
	if ((*word = ft_strdup(tmp)) == NULL)
	{
		free(tmp);
		return (ERROR);
	}
	free(tmp);
	return (SUCCESS);
}

void	copy_word_except_quote(char *dest, char *src)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\'' || src[i] == '\"')
		{
			quote = src[i++];
			while (src[i] != quote)
				dest[j++] = src[i++];
			i++;
			continue;
		}
		dest[j++] = src[i++];
	}
	dest[j] = '\0';
}
