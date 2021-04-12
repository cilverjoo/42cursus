#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TYPE_PIPE 1
#define SIDE_IN   0
#define SIDE_OUT  1

#define STDIN		0
#define STDOUT		1
#define STDERR		2

#define TYPE_BREAK 2

typedef struct		s_list
{
    char        **args;
    int             length;
    int             type;
    int             pipes[2];
    struct s_list   *prev;
    struct s_list   *next;
}					t_list;



int			exec_cmd(t_list *cmd, char **env)
{
	pid_t	pid;
	int		ret;
	int		status;
	int		pipe_open;

	ret = EXIT_FAILURE;
	pipe_open = 0;
	if (cmd->type == TYPE_PIPE || (cmd->prev && cmd->prev->type == TYPE_PIPE))
	{
		pipe_open = 1;
		if (pipe(cmd->pipes))
			return (exit_fatal());
	}
	pid = fork();
	if (pid < 0)
		return (exit_fatal());
	if (pid == 0)
	{
		if (cmd->type == TYPE_PIPE
			&& dup2(cmd->pipes[SIDE_IN], STDOUT) < 0)
			return (exit_fatal());
		if (cmd->prev && cmd->prev->type == TYPE_PIPE
			&& dup2(cmd->prev->pipes[SIDE_OUT], STDIN) < 0)
			return (exit_fatal());
		if ((ret = execve(cmd->args[0], cmd->args, env)) < 0)
		{
			show_error("error: cannot execute ");
			show_error(cmd->args[0]);
			show_error("\n");
		}
		exit(ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (pipe_open)
		{
			close(cmd->pipes[SIDE_IN]);
			if (!cmd->next || cmd->type == TYPE_BREAK)
				close(cmd->pipes[SIDE_OUT]);
		}
		if (cmd->prev && cmd->prev->type == TYPE_PIPE)
			close(cmd->prev->pipes[SIDE_OUT]);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
	}
	return (ret);
}

int 		exec_cmds(t_list **cmds, char **env)
{
	t_list	*crt;
	int		ret;

	ret = EXIT_SUCCESS;
	while (*cmds)
	{
		crt = *cmds;
		if (strcmp("cd", crt->args[0]) == 0)
		{
			if (crt->length < 2)
				ret = show_error("error: cd: bad arguments\n");
			else if (chdir(crt->args[1]))
			{
				ret = show_error("error: cd: cannot change directory tp ");
				show_error(crt->args[1]);
				show_error("\n");
			}
		}
		else
			exec_cmd(cmds, env);
		*cmds = (*cmds)->next;
	}
	return (ret);
}

int			list_clear(t_list **cmds)
{
	t_list	*tmp;
	int		i;

	while (*cmds)
	{
		tmp = (*cmds)->prev;
		i = 0;
		while (i < (*cmds)->length)
			free((*cmds)->args[i++]);
		free((*cmds)->args);
		free(*cmds);
		*cmds = tmp;
	}
	*cmds = NULL;
	return (EXIT_SUCCESS);
}

int			main(int ac, char **av, char **env)
{
	t_list	*cmds;
	int		i;
	int		ret;

	ret = EXIT_SUCCESS;
	cmds = NULL;
	i = 1;
	while (i < ac)
		parse_args(&cmds, av[i++]);
	list_rewind(&cmds);
	if (cmds)
		exec_cmds(&cmds, env);
	list_clear(&cmds);
	return (ret);
}