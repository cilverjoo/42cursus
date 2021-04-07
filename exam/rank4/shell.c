#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIDE_OUT    0
#define SIDE_IN     1

#define STDIN       0
#define STDOUT      0
#define STDERR      2

#define TYPE_END    0
#define TYPE_PIPE   1
#define TYPE_BREAK  2

#define TEST        0

typedef struct		s_list
{
    char            **args;
    int             length;
    int             type;
    int             pipes[2];
    struct s_list   *prev;
    struct s_list   *next;
}					t_list;

int         exit_fatal(void)
{
    show_error("error: fatal\n");
    exit(EXIT_FAILURE);
    return (EXIT_FAILURE);
}

int         add_arg(t_list *cmd, char *arg)
{
    char    **tmp;
    int     i;
    
    i = 0;
    tmp = NULL;
    if (!(tmp = (char **)malloc(sizeof(*tmp) * (cmd->length + 2))))
        return (exit_fatal());
    while (i < cmd->length)
    {
        tmp[i] = cmd->args[i];
        i++;
    }
    if (cmd->length > 0)
        free(cmd->args);
    cmd->args = tmp;
    cmd->args[i++] = ft_strdup(arg);
    cmd->args[i] = 0;
    cmd->length++;
    return (EXIT_SUCCESS);
}

int         list_push(t_list **list, char *arg)
{
    t_list  *new;
    
    if (!(new = (t_list *)malloc(sizeof(t_list))))
        return (exit_fatal());
    new->args = NULL;
    new->length = 0;
    new->type = TYPE_END;
    new->prev = NULL;
    new->next = NULL;
    if (*list)
    {
        (*list)->next = new;
        new->prev = *list;
    }
    *list = new;
    return (add_arg(new, arg));
}

int         parse_arg(t_list **cmds, char *arg)
{
    int     is_break;
    
    is_break = (strcmp(";", arg) == 0);
    if (is_break && !*cmds)
        return (EXIT_SUCCESS);
    else if (!is_break && (!*cmds || (*cmds)->type > TYPE_END))
        return (list_push(cmds, arg));
    else if (strcmp("|", arg) == 0)
        (*cmds)->type = TYPE_PIPE;
    else if (is_break)
        (*cmds)->type = TYPE_BREAK;
    else
        return (add_arg(*cmds, arg));
    return (EXIT_SUCCESS);
}

int         list_rewind(t_list **list)
{
    while (*list && (*list)->prev)
        *list = (*list)->prev;
    return (EXIT_SUCCESS);
}

int         ft_strlen(char *str)
{
    int     i;
    
    i = 0;
    while (str[i])
        i++;
    return (i);
}

int         show_error(char const *str)
{
    if (str)
        write(STDERR, str, ft_strlen(str));
    return (EXIT_FAILURE);
}

int         exec_cmd(t_list *cmd, char **env)
{
    pid_t   pid;
    int     ret;
    int     status;
    int     pipe_open;
    
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
    else if (pid == 0)
    {
        if (cmd->type == TYPE_PIPE && dup2(cmd->pipes[SIDE_IN], STDOUT) < 0)
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
            ret = WEXITSTATUS(status)''
    }
    
}


int         exec_cmds(t_list **cmds, char **env)
{
    t_list  *crt;
    int     ret;
    
    ret = EXIT_SUCCESS;
    list_rewind(cmds);
    while (*cmds)
    {
        crt = *cmds;
        if (strcmp("cd", crt->args[0]) == 0)
        {
            ret = EXIT_SUCCESS;
            if (crt->length < 2)
                ret = show_error("error: cd: bad arguments\n");
            else if (chdir(crt->args[1]))
            {
                ret = show_error("error: cd: cannot change directory to ");
                show_error(crt->args[1]);
                show_error("\n");
            }
        }
        else
            ret = exec_cmds(crt, env);
        if (!(*cmds)->next)
            break ;
        *cmds = (*cmds)->next;
    }
    return (ret);
}

int         main(int ac, char **av, char **env)
{
    t_list  *cmds;
    int     i;
    int     ret;
    
    ret = EXIT_SUCCESS;
    cmds = NULL;
    i = 1;
    while (i < ac)
        parse_arg(&cmds, av[i++]);
    if (cmds)
        ret = exec_cmds(&cmds, env);
}
