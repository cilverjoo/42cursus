/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kim-eunju <kim-eunju@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:27:23 by heryu             #+#    #+#             */
/*   Updated: 2021/02/21 15:41:11 by kim-eunju        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft.h"
# include "../lib/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>

# define STDIN		0
# define STDOUT		1
# define STDERROR	2

# define S_OUTER	1
# define S_INNER	2
# define D_OUTER	3
# define D_INNER	4
# define NO_QUOTE	5

# define ERROR		0
# define SUCCESS	1
# define INVALID	0
# define VALID		1
# define FALSE		0
# define TRUE		1

# define READ	0
# define WRITE	1

# define EMPTY	0
# define CMD	1
# define ARG	2
# define FILE	3
# define END	4
# define PIPE	5
# define INPUT	6
# define OUTPUT	7
# define ADD	8

typedef struct		s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_token
{
	char			*word;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct		s_shell
{
	char			*name;
	char			*old_dir;
	char			*cur_dir;
	char			*home_dir;
	char			*line;
	struct s_env	*env_list;
	struct s_env	*export_list;
	struct s_token	*tokens;
	char			**cmd;
	int				pio[2];
	int				origin_std[2];
	int				exit_status;
	pid_t			pid;
	int				exit_child;
	int				wating_child;
}					t_shell;

extern t_shell		g_minishell;

/*
** signal
*/
void				sighandler_int(int signum);
void				sighandler_quit(int signum);

/*
** parsing
*/
int					parsing(t_shell *minishell);
int					read_line(t_shell *minishell);
int					make_space_sep_line(t_shell *minishell);
int					make_token(t_shell *minishell);

/*
** token
*/
int					make_a_token(t_shell *minishell, int *i);
t_token				*get_last_token(t_token *token);
t_token				*create_new_token(void);
void				specify_token_type(t_token *token);
int					get_token_type(t_token *token);

/*
** line
*/
int					get_space_sep_line_size(char *line);
void				copy_space_sep_line(char *line, char *n_l, int i, int j);

/*
** quote
*/
int					is_escape_quote(char *line, int index);
int					check_io_quote(char *line, size_t index);
int					remove_quote_in_word(char **word);
void				copy_word_except_quote(char *dest, char *src);

/*
** escape
*/
int					get_backslash_char_cnt(char *line);
void				copy_except_backslash_char(char *line, char *n_l, int idx);
int					remove_backslash_char(t_shell *minishell);
int					make_escape_env_char_negative(t_shell *minishell);
int					toggle_negative_char(char *word);

/*
** clear
*/
int					clear_env(t_env *list, int ret);
int					clear_line(t_shell *minishell, int ret);
int					clear_tokens(t_shell *minishell, int ret);
int					clear_cmd(t_shell *minishell, int ret);
int					clear_all(t_shell *minishell, int status, int is_exit);

/*
** valid
*/
int					is_valid_token_type(t_token *token);
int					is_valid_escape(t_shell *minishell);
int					is_valid_ascii(t_shell *minishell);
int					is_valid_quote(t_shell *minishell);

/*
** exec
*/
int					execute(t_shell *minishell);
void				reset_std_fd(t_shell *minishell);
int					make_clean_word(t_env *env_list, t_token *token);

/*
** cmd
*/
int					execute_cmd(t_shell *mini, t_token *token);
int					make_cmd(t_shell *mini, t_token *token);
int					get_cmd_size(t_token *token);
int					set_cmd_absolute_path(t_shell *mini);
int					print_exec_error(t_shell *mini);

/*
** redir
*/
int					set_redir(t_token *token);
int					set_add_redir(t_token *token);
int					set_output_redir(t_token *token);
int					set_input_redir(t_token *token);

/*
** pipe
*/
void				next_pipe_redir(int *pio);
void				prev_pipe_redir(int *pio);

/*
** get_env
*/
char				**get_env_path(t_env *env_list);
char				**get_env(t_env *env_list);
char				*get_env_value(t_env *env, char *key);
int					get_env_cnt(t_env *env_list);

/*
** replace env_value
*/
int					word_to_env_value(t_env *env_list, char **word);
int					ft_strcat_exit_str(char **cur_word, int *i);
int					ft_strcat_normal_str(char *org_w, char **cur_w, int *i);
int					ft_strcat_env_str(char *o_w, char **c_w, int *i, t_env *e);

/*
** get_token
*/
t_token				*get_next_run_token(t_token *token);
t_token				*get_next_pipe(t_token *token);
t_token				*get_prev_pipe(t_token *token);
t_token				*get_next_cmd(t_token *token);
t_token				*get_prev_cmd(t_token *token);

/*
** builtin
*/
int					add_new_env(t_env *list, char *key, char *value);
int					check_existing_key(t_env *list, char *key);
int					replace_env_node(t_env *list, char *key, char *value);
t_env				*new_env_node(char *key, char *value);
int					init_env(t_shell *minishell, char **envp);

int					cmd_export(char **cmd, t_shell *minishell, t_token *token);
int					sort_export_list(t_env **exp_head);
int					make_export_list(t_shell *minishell);

int					cmd_cd(char **cmd, t_shell *minishell);
char				*get_value_from_key(t_shell *minishell, char *key);

int					cmd_unset(char **cmd, t_shell *minishel, t_token *token);
int					unset_this_env(t_env *list, char *key);

int					cmd_env(t_shell *minishell);

int					cmd_echo(char **cmd);

int					cmd_pwd(t_shell *minishell);

int					cmd_exit(char **cmd, t_shell *minishell, t_token *token);

/*
** utils0
*/
int					skip_space(char *line, int *i);
int					is_sep(char ch);
int					is_space(char ch);

/*
** utils1
*/
void				free_ppmem(char **pp);
char				*get_value_from_key(t_shell *minishell, char *key);
int					check_valid_key(char *cmd);
int					find_equals(char *cmd);

#endif
