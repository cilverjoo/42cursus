#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct		s_list
{
    char        **args;
    int             length;
    int             type;
    int             pipes[2];
    struct s_list   *prev;
    struct s_list   *next;
}					t_list;

int			main(int ac, char **av, char **env)
{
	t_list	*cmds;
	int		i;
	int		ret;
	
	ret = EXIT_SUCCESS;
	
}
