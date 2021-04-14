#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define ERR1	"error: cd: bad arguments\n"
#define ERR2	"error: cd: cannot change directory to "
#define ERR3	"error: fatal\n"
#define ERR4	"error: cannot execute "

int		is_pipe(char **argv)
{
	int	i=-1;

	while (argv[++i])
	{
		if (!strncmp(argv[i], "|", 2))
		{
			argv[i] = NULL;
			return (1);
		}
		else if (!strncmp(argv[i], ";", 2))
		{
			argv[i] = NULL;
			return (0);
		}
	}
	return (0);
}

int		ft_strlen(char *s)
{
	int	i=0;

	while (s[i])
		i++;
	return (i);
}

int		put_error(char *s)
{
	write(2, s, ft_strlen(s));
	return (1);
}

int		ft_argvlen(char **argv)
{
	int	i=0;

	while (argv[i])
		i++;
	return (i);
}

void	ft_cd(char **argv)
{
	int	i = ft_argvlen(argv);

	if (i != 2)
		put_error(ERR1);
	else if (chdir(argv[1]) < 0)
	{
		put_error(ERR2);
		put_error(argv[1]);
		put_error("\n");
	}
}

void	cmd(int argc, char **argv, char **envp, int prev, int *fd_prev)
{
	pid_t	pid;
	int		fd_next[2];
	int		next, status, i;

	if (argc <= 0)
		return ;
	next = is_pipe(argv);
	if (argv[0])
	{
		if (next && pipe(fd_next) < 0)
			exit(put_error(ERR3));
		if (!strncmp(argv[0], "cd", 3))
			ft_cd(argv);
		else if ((pid = fork()) < 0)
			exit(put_error(ERR3));
		else if (!pid)
		{
			if (prev && dup2(fd_prev[0], 0) < 0)
				exit(2);
			if (next && dup2(fd_next[1], 1) < 0)
				exit(2);
			if (execve(argv[0], argv, envp) < 0)
			{
				put_error(ERR4);
				put_error(argv[0]);
				put_error("\n");
				exit(1);
			}
		}
		else
		{
			if (waitpid(pid, &status, 0) < 0)
				exit(put_error(ERR3));
			if (status == 512)
				exit(put_error(ERR3));
			if (prev)
				close(fd_prev[0]);
			if (next)
				close(fd_next[1]);
		}
	}
	i = ft_argvlen(argv);
	cmd(argc-i-1, argv+i+1, envp, next, fd_next);
}

int		main(int argc, char **argv, char **envp)
{
	int	fd_prev[2];

	fd_prev[0] = 0;
	fd_prev[1] = 1;
	cmd(argc-1, argv+1, envp, 0, fd_prev);
	return (0);
}
