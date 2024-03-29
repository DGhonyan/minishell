/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dghonyan <dghonyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:19:51 by dghonyan          #+#    #+#             */
/*   Updated: 2022/09/09 18:59:44 by dghonyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <stdbool.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>

# ifdef LINUX
#  include <readline/history.h>
#  include <readline/readline.h>
# else
#  include "readline/history.h"
#  include "readline/readline.h"
# endif

# include "colors.h"
# include "libft/libft.h"

# define NF 127
# define CE 126

typedef struct s_exec
{
	char	*exec;
	char	**argv;
}	t_exec;

typedef struct s_fds
{
	int		len;
	int		flags;
	int		fd;
	int		to;
	int		from;
	int		append;
	int		heredoc;
	int		quoted;
	char	*here;
}	t_fds;

typedef struct s_cmd
{
	int		len;
	int		envp_count;
	char	*pwd;
	char	*oldpwd;
	int		*status;
	char	*line;
	char	*command;
	char	**envp;
	char	**new_env;
	t_fds	*fds;
	t_exec	exec;
}	t_cmd;

typedef struct s_exp
{
	int		i;
	int		j;
	char	*s;
	char	*res;
	t_cmd	*cmd;
}	t_exp;

int			dir(char *s);
int			valid_red(char *line);
int			is_signaled(t_cmd *cmd);
int			has_an_error(t_cmd *cmd, int i);
int			strcmp_minishell(char *s);
int			count_pipes(char *s);
int			init_pipes(int (*pipes)[2], int size, int cond);
int			dup_pipes(t_cmd *cmd, int i, int (*pipes)[2], int size);
int			close_pipes(int (*pipes)[2], int size);
int			is_in_env(char **env, char *key);
int			ft_strcmp_env(char *s1, char *s2);
int			find_index(char *s, char c);
int			children(t_cmd *cmd, int (*pipes)[2], int size, int i);
int			redirection_count(char *s, int i, int count);
int			last_fd(t_cmd *cmd, int i, int cond);
int			var_len(char *s, int i, int quote);
int			is_a_valid_name(char c, int cond);
int			expanded_len(char *cmd, int i, int quote, t_cmd *cmd1);
int			call_forks(t_cmd *cmd, char *line);
int			call_builtins(t_cmd *cmd, int i, int single);
int			heredoc(char *limiter, int quoted, t_cmd *cmd);
int			redirection_index(char *cmd, int i);
int			perror_ret(char *msg);
int			perror_neg(char *msg);
int			check_quotes(char *s);
int			is_a_builtin(char *s);
int			exec_argv(t_cmd *cmd, int i, int j);
int			stderror_putstr(char *s1, char *s2, char *s3, int cond);
int			perror_builtins(int status, char *s1, char *s2, char *s3);
int			init_fds(t_fds *fds, char *s, char *filename, t_cmd *cmd);
int			not_found(char *exec);
void		export_print(char *s, int fd);
void		close_pipes_parent(int len, int (*pipes)[2]);
void		to_from(t_cmd *cmd);
void		perror_exit_free(t_cmd *cmd, char *s, char *msg, int cond);
void		replace_env(char **old_env, char *key, char *value, t_cmd *cmd);
void		set_cmd(t_cmd *cmd, char *line, int *status, char **new_env);
void		remove_env(char **envp, char *key);
void		strjoin_var(char *s1, char *s2);
void		perror_exit(t_cmd *cmd, char *msg, int cond);
void		init_signals_parent(void);
void		init_signals_child(void);
void		init_signals_heredoc(void);
void		free_cmd(t_cmd *cmd);
void		free_fds(t_fds *fds);
char		*getoldpwd(char *oldpwd, int mode);
char		*_getenv(char **envp, char *s, t_cmd *cmd);
char		*ft_strdup_env(char *key, char *value);
char		*_key(char *s, t_cmd *cmd);
char		*_value(char *s, t_cmd *cmd);
char		*expanded_env(char *cmd, int i, int quote, t_cmd *cmd1);
char		*get_path(t_cmd *cmd, char *command);
char		*expand_line(char *cmd, t_cmd *cmd1);
char		**_env(char **old_env, char *val, t_cmd *cmd);
char		**copy_env(char **envp, int i, char *cwd);
char		**filter_argv(char **argv, t_cmd *cmd, int k);
char		**env(char **old_env, char *key, char *value, t_cmd *cmd);
char		**init_main(char **ep, char **av, char **pwd, struct termios *old);
t_fds		*open_files(t_cmd *cmd, char *s, int i, int j);
t_cmd		*parse_line(char *line, char **envp);
t_fds		*alloc_fds(int size);
__int128_t	int_128_atoi(char *s);

#endif