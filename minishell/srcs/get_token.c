/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:22:28 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 14:23:38 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_next_run_token(t_token *token)
{
	while (token && token->type != END && token->type != PIPE)
		token = token->next;
	if (token && (token->type == END || token->type == PIPE))
		token = token->next;
	return (token);
}

t_token	*get_prev_cmd(t_token *token)
{
	t_token *ret_token;

	if (token && (token->type == END || token->type == PIPE))
		token = token->prev;
	ret_token = NULL;
	while (token && token->type != END && token->type != PIPE)
	{
		if (token->type == CMD)
			ret_token = token;
		token = token->prev;
	}
	return (ret_token);
}

t_token	*get_next_cmd(t_token *token)
{
	t_token *ret_token;

	if (token && (token->type == END || token->type == PIPE))
		token = token->next;
	ret_token = NULL;
	while (token && token->type != END && token->type != PIPE)
	{
		if (token->type == CMD)
			ret_token = token;
		token = token->next;
	}
	return (ret_token);
}

t_token	*get_prev_pipe(t_token *token)
{
	t_token *ret_token;

	ret_token = NULL;
	while (token && token->type != END)
	{
		if (token->type == PIPE)
			ret_token = token;
		token = token->prev;
	}
	return (ret_token);
}

t_token	*get_next_pipe(t_token *token)
{
	t_token *ret_token;

	ret_token = NULL;
	while (token && token->type != END)
	{
		if (token->type == PIPE)
			ret_token = token;
		token = token->next;
	}
	return (ret_token);
}
