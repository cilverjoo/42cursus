/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:21:38 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 13:23:02 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_token_type(t_token *token)
{
	char	*word;
	int		prev_token_type;

	word = token->word;
	prev_token_type = (token->prev == NULL) ? EMPTY : token->prev->type;
	if (ft_strcmp(";", word) == 0)
		return (END);
	else if (ft_strcmp("|", word) == 0)
		return (PIPE);
	else if (ft_strcmp("<", word) == 0)
		return (INPUT);
	else if (ft_strcmp(">", word) == 0)
		return (OUTPUT);
	else if (ft_strcmp(">>", word) == 0)
		return (ADD);
	else
	{
		if (INPUT <= prev_token_type && prev_token_type <= ADD)
			return (FILE);
		else if (!get_prev_cmd(token))
			return (CMD);
		else
			return (ARG);
	}
}

void	specify_token_type(t_token *token)
{
	while (token)
	{
		token->type = get_token_type(token);
		token = token->next;
	}
}

t_token	*create_new_token(void)
{
	t_token	*ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (ret == NULL)
		return (ERROR);
	ft_memset(ret, 0, sizeof(t_token));
	return (ret);
}

t_token	*get_last_token(t_token *token)
{
	if (token == NULL)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}

int		make_a_token(t_shell *minishell, int *i)
{
	t_token	*new_token;
	t_token *prev_token;
	char	*line;
	int		pivot;

	pivot = *i;
	line = minishell->line;
	prev_token = get_last_token(minishell->tokens);
	while (line[*i] &&
			(!is_space(line[*i]) || check_io_quote(line, *i) % 2 == 0))
		(*i)++;
	if ((new_token = create_new_token()) == NULL)
		return (ERROR);
	if (prev_token == NULL)
		minishell->tokens = new_token;
	else
		prev_token->next = new_token;
	if ((new_token->word = ft_substr(line, pivot, *i - pivot)) == NULL)
		return (ERROR);
	new_token->next = NULL;
	new_token->prev = prev_token;
	return (SUCCESS);
}
