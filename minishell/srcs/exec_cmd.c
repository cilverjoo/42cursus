/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heryu <heryu@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:16:11 by heryu             #+#    #+#             */
/*   Updated: 2021/02/21 13:16:19 by heryu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		print_exec_error(t_shell *mini)
{
	char	**cmd;
	DIR		*p_dir;

	cmd = mini->cmd;
	ft_putstr_fd("minishell: ", STDERROR);
	ft_putstr_fd(cmd[0], STDERROR);
	if (ft_strchr(cmd[0], '/') == NULL)
	{
		ft_putstr_fd(": command not found\n", STDERROR);
		return (127);
	}
	if ((p_dir = opendir(cmd[0])) == NULL)
	{
		ft_putstr_fd(":  No such file or directory\n", STDERROR);
		return (1);
	}
	else
	{
		ft_putstr_fd(": is a directory\n", STDERROR);
		closedir(p_dir);
		return (126);
	}
}

int		set_cmd_absolute_path(t_shell *mini)
{
	char			**path;
	int				i;
	DIR				*p_dir;
	struct dirent	*dir_ent;

	path = get_env_path(mini->env_list);
	i = -1;
	while (path[++i])
	{
		if ((p_dir = opendir(path[i])) == NULL)
			continue ;
		while ((dir_ent = readdir(p_dir)) != NULL)
		{
			if (ft_strcmp(mini->cmd[0], dir_ent->d_name) == 0)
			{
				mini->cmd[0] = ft_strjoin_free("/", mini->cmd[0], 0, 1);
				mini->cmd[0] = ft_strjoin_free(path[i], mini->cmd[0], 0, 1);
				free_ppmem(path);
				return (SUCCESS);
			}
		}
		closedir(p_dir);
	}
	free_ppmem(path);
	return (ERROR);
}

int		get_cmd_size(t_token *token)
{
	int		size;

	size = 0;
	while (token && token->type != END && token->type != PIPE)
	{
		if (token->type == CMD || token->type == ARG)
			size++;
		token = token->next;
	}
	return (size);
}

int		make_cmd(t_shell *mini, t_token *token)
{
	t_token	*cmd_token;
	int		i;

	cmd_token = get_next_cmd(token);
	mini->cmd = (char **)malloc(sizeof(char *) * (get_cmd_size(cmd_token) + 1));
	if (mini->cmd == NULL)
		return (ERROR);
	i = 0;
	while (token && token->type != END && token->type != PIPE)
	{
		if (token->type == CMD || token->type == ARG)
		{
			mini->cmd[i] = ft_strdup(token->word);
			if (mini->cmd[i] == NULL)
				return (ERROR);
			i++;
		}
		token = token->next;
	}
	mini->cmd[i] = NULL;
	return (SUCCESS);
}

int		execute_cmd(t_shell *mini, t_token *token)
{
	char	**envp;
	int		status;

	status = -1;
	mini->exit_child = FALSE;
	mini->pid = fork();
	if (mini->pid == 0)
	{
		if (ft_strchr(mini->cmd[0], '/') == NULL)
			set_cmd_absolute_path(mini);
		envp = get_env(mini->env_list);
		execve(mini->cmd[0], mini->cmd, envp);
		free_ppmem(envp);
		status = print_exec_error(mini);
		clear_all(mini, status, TRUE);
		exit(status);
	}
	else if (!get_next_pipe(token))
		waitpid(mini->pid, &status, 0);
	if (mini->exit_child == FALSE && status != -1)
		mini->exit_status = (status >> 8);
	mini->pid = 0;
	return (SUCCESS);
}
