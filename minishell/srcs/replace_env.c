/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:36:16 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 14:37:00 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_strcat_exit_str(char **cur_word, int *i)
{
	char	*status;
	char	*ret;

	*i += 2;
	if ((status = ft_itoa(g_minishell.exit_status)) == NULL)
		return (ERROR);
	if ((ret = ft_strjoin(*cur_word, status)) == NULL)
	{
		free(status);
		return (ERROR);
	}
	free(*cur_word);
	free(status);
	*cur_word = ret;
	return (SUCCESS);
}

int		ft_strcat_env_str(char *org_word, char **cur_word, int *i, t_env *env)
{
	char	*key;
	char	*value;
	char	*ret;
	int		pivot;

	pivot = ++(*i);
	while (ft_isdigit(org_word[*i]) || ft_isalpha(org_word[*i]))
		(*i)++;
	if ((key = ft_substr(org_word, pivot, (*i) - pivot)) == NULL ||
		(value = get_env_value(env, key)) == NULL)
	{
		free(key);
		return (ERROR);
	}
	if ((ret = ft_strjoin(*cur_word, value)) == NULL)
	{
		free(key);
		free(value);
		return (ERROR);
	}
	free(key);
	free(value);
	free(*cur_word);
	*cur_word = ret;
	return (SUCCESS);
}

int		ft_strcat_normal_str(char *org_word, char **cur_word, int *i)
{
	int		pivot;
	char	*normal_str;
	char	*ret;

	pivot = *i;
	while (org_word[*i] && org_word[*i] != '$')
		(*i)++;
	if ((normal_str = ft_substr(org_word, pivot, *i - pivot)) == NULL)
		return (ERROR);
	if ((ret = ft_strjoin(*cur_word, normal_str)) == NULL)
	{
		free(normal_str);
		return (ERROR);
	}
	free(normal_str);
	free(*cur_word);
	*cur_word = ret;
	return (SUCCESS);
}

int		word_to_env_value(t_env *env_list, char **word)
{
	int		i;
	char	*cur_word;

	cur_word = NULL;
	i = 0;
	while ((*word)[i])
	{
		if ((*word)[i] == '$')
		{
			if ((*word)[i + 1] == '?')
				ft_strcat_exit_str(&cur_word, &i);
			else
				ft_strcat_env_str(*word, &cur_word, &i, env_list);
		}
		else
			ft_strcat_normal_str(*word, &cur_word, &i);
	}
	free(*word);
	*word = cur_word;
	return (SUCCESS);
}
