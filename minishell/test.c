#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		main(int ac, char **av, char **envp)
{
		
	if (execve("ls", "-al") == -1)
	{
		write(2, strerr:or(errno), strlen(strerror(errno)));
	}
	return (0);
}
