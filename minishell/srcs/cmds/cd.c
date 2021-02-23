/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:16:11 by kim-eunju         #+#    #+#             */
/*   Updated: 2021/02/21 17:45:07 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			update_old_cur_dir(t_shell *mini, char *new_dir)
{
	char	*old;

	old = mini->old_dir;
	mini->old_dir = mini->cur_dir;
	mini->cur_dir = new_dir;
	replace_env_node(mini->env_list, "OLDPWD", ft_strdup(mini->old_dir));
	replace_env_node(mini->export_list, "OLDPWD", ft_strdup(mini->old_dir));
	replace_env_node(mini->env_list, "PWD", ft_strdup(new_dir));
	replace_env_node(mini->export_list, "PWD", ft_strdup(new_dir));
	free(old);
	return (SUCCESS);
}

char		*get_parent_dir(char *cur_dir)
{
	int		i;

	if (ft_strcmp(cur_dir, "/") == 0)
		return (ft_strdup("/"));
	i = ft_strlen(cur_dir) - 1;
	while (i > 0)
	{
		if (cur_dir[i] == '/')
			return (ft_substr(cur_dir, 0, i));
		i--;
	}
	return (ERROR);
}

int			cd_only(t_shell *minishell)
{
	if (check_existing_key(minishell->env_list, "HOME"))
	{
		chdir(minishell->home_dir);
		update_old_cur_dir(minishell, getcwd(NULL, 0));
	}
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERROR);
		minishell->exit_status = 1;
		return (ERROR);
	}
	return (SUCCESS);
}

int			cd_move_to_path(t_shell *minishell, char *path)
{
	int		ret;

	ret = chdir(path);
	if (ret == 0)
		update_old_cur_dir(minishell, getcwd(NULL, 0));
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERROR);
		ft_putstr_fd(path, STDERROR);
		ft_putstr_fd(": ", STDERROR);
		ft_putstr_fd(strerror(errno), STDERROR);
		ft_putstr_fd("\n", STDERROR);
		minishell->exit_status = 1;
		return (ERROR);
	}
	return (SUCCESS);
}

int			cmd_cd(char **cmd, t_shell *minishell)
{
	char	*new_dir;

	if (!cmd[1])
		return (cd_only(minishell));
	else if (ft_strcmp(cmd[1], "~") == 0)
	{
		chdir(minishell->home_dir);
		update_old_cur_dir(minishell, getcwd(NULL, 0));
	}
	else if (ft_strcmp(cmd[1], ".") == 0)
	{
		new_dir = ft_strdup(minishell->cur_dir);
		update_old_cur_dir(minishell, new_dir);
	}
	else if (ft_strcmp(cmd[1], "..") == 0)
	{
		new_dir = get_parent_dir(minishell->cur_dir);
		chdir(new_dir);
		update_old_cur_dir(minishell, new_dir);
	}
	else
		return (cd_move_to_path(minishell, cmd[1]));
	return (SUCCESS);
}
