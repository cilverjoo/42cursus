/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:33:06 by heryu             #+#    #+#             */
/*   Updated: 2021/02/18 14:34:24 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

int		get_env_cnt(t_env *env_list)
{
	int		cnt;
	t_env	*env;

	cnt = 0;
	env = env_list;
	while (env)
	{
		cnt++;
		env = env->next;
	}
	return (cnt);
}

char	**get_env_path(t_env *env_list)
{
	char	*tmp;
	char	**path;

	if ((tmp = get_env_value(env_list, "PATH")) == NULL)
		return (ERROR);
	if ((path = ft_split(tmp, ':')) == NULL)
	{
		free(tmp);
		return (ERROR);
	}
	free(tmp);
	return (path);
}

char	**get_env(t_env *env_list)
{
	char	**ret;
	t_env	*env;
	int		i;
	char	*tmp;

	ret = (char **)malloc(sizeof(char *) * (get_env_cnt(env_list) + 1));
	if (ret == NULL)
		return (ERROR);
	i = 0;
	env = env_list;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		ret[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	ret[i] = NULL;
	return (ret);
}
