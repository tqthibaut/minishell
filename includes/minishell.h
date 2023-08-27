/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:51:59 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 12:18:38 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>

extern int	g_exit_status;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}				t_env;

typedef struct s_list_env
{
	struct s_env	*envp;
	struct s_env	*exp;
	char			**tab_env;
}				t_list_env;

typedef struct s_arg
{
	char			*str;
	int				quote;
	int				null;
	struct s_arg	*next;
}					t_arg;

typedef struct s_pipe
{
	int	nbpipe;
	int	*pipefd;
}				t_pipe;

typedef struct s_arg_info
{
	int					index;
	int					i;
	int					size;
	int					execute;
	char				**cmd;
	int					*tab_null;
	char				*newcmd;
	int					infilefd;
	int					outfilefd;
	char				*infile_name;
	int					heredoc_expansion;
	int					is_in;
	int					is_out;
	pid_t				childpid;
	struct s_arg_info	*next;
}				t_arg_info;

typedef struct s_info
{
	char				*buffer;
	char				*cmd_error;
	struct s_arg		*arg;
	struct s_arg		*current_arg;
	struct s_list_env	list_env;
	struct s_pipe		pipe;
	struct s_arg_info	*list_arg;
	struct s_arg_info	*current_list_arg;
	int					fdsave[2];
	int					sig_int;
	int					parent_status;
}				t_info;

typedef struct s_index_exp
{
	int		i;
	int		u;
	int		word_tab;
	int		ind_tab;
	int		singleq;
	int		doubleq;
}				t_index_exp;

typedef enum e_error
{
	NB_ARGUMENT,
	CMD_NOT_FOUND,
	MALLOC,
	FD_ERROR,
	SYNTAX,
	AMBIGUOUS,
	IS_DIR,
	PERMISSION
}				t_error;

/* ACCESS */
int		check_access(t_info *info);
void	which_dup(t_info *info);
void	reset_dup(t_info *info);

/* BUILT IN */
int		built_in_exit(t_info *info);
int		built_in_pwd(t_info *info);
int		built_in_env(t_info *info);
int		built_in_export(t_info *info);
int		add_export(t_info *info, char *str);
int		add_env(t_info *info, char *str);
int		built_in_unset(t_info *info);
void	find_and_unset(char *str, t_env *exp, t_info *info);
int		check_unset_flag(t_info *info);
void	child_unset(t_info *info);
int		built_in_echo(t_info *info);
int		built_in_cd(t_info *info);
void	child_cd(t_info *info);
char	*parse_cd(t_arg_info *arg);
int		check_path(char *path, char *cmd);
int		change_env(t_env *envp, char *path, int type, t_env *tmp_pwd);
char	*absolute_path(t_arg_info *arg);
char	*relative_path(char **split_path, const char *current_path);
int		check_built_in(char *str);
int		go_to_built_in(t_info *info);

/* COMMAND */
int		parse_cmd(t_info *info);
int		do_command(t_info *info);
int		command_part(t_info *info);

/* ENV */
t_env	*init_env(char **envp, int type);
int		change_sh_level(t_env *env, int type);
int		add_quote(t_env *ret);
int		get_tab_env(t_info *info);
t_env	*init_null(int type);
t_env	*find_env(t_env *env, char *str, int type);
t_env	*null_export(char *string, int type);
t_env	*null_env(char *string, int type);

/* ERROR */
int		print_error(int code, char *str);

/* EXPANSION */
char	*replace_expansion(t_info *info, char *str);
void	check_current_quote(char c, int *singleq, int *doubleq);
int		total_exp(char *str, int singleq, int doubleq, int count);
int		find_quote(char *str);
void	replace_quote_tab(char **replace_exp);
int		count_exp_word_remove(char *str);
char	*content_exp(char *str);
int		length_exp(char *str, int i);
char	*find_exp(char *str, int *i, t_env *env, int *doubleq);

/* FREE */
void	static_magic(t_info *mem);
void	tab_free(char ***tab);
void	free_list_env(t_list_env *env);
void	free_arg(t_arg **arg);
void	free_info(t_info *info);
void	free_list_arg(t_arg_info **list);
void	reset_free(t_info *info);
void	free_all_no_unlink(t_info *info);
void	free_all_with_unlink(t_info *info);
void	close_fd(t_arg_info *tmp);
void	free_env(t_env *env);
t_arg	*free_null_arg_list(t_info *info, t_arg *arg);

/* HEREDOC */
int		heredoc_create_file(t_arg_info *list, int index);
void	heredoc_read(t_arg_info *list, char *delimiter, t_info *info);
void	close_and_unlink(t_info *info);
int		heredoc_open(t_arg_info *list, int type);

/* LIST */
t_env	*create_list_env(char *str, int type);
void	print_list(t_env *envp);

/* LIBFT */
int		get_next_line(int fd, char **line);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *s, char c);
size_t	ft_strlen(const char *s);
int		ft_atoi(const char *str);
void	ft_lstadd_back(t_env **alst, t_env *new);
size_t	ft_strlcpy(char *dest, const char *src, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memset(void *s, int c, size_t n);
int		ft_isalnum(int c);
int		ft_isdigit(int c);

/* PARSING */
int		get_arg_length(char *buffer, int i);
int		split_arg(t_info *info);
int		get_arg(t_info *info);
t_arg	*new_arg(char *buffer, int *i);
int		check_buffer(t_info *info);
int		check_redirection(char *buffer);
int		check_pipe(char *buffer);
char	*realloc_parsing_space(char *buffer, int i, int u, char quote);
int		count_quote(char *delimiter, int i, int count);
char	*remove_quotes(char	*str);
int		quick_check_quote(char *str);
int		is_pipe(t_arg *arg);
void	free_null_tab(t_info *info);
int		get_cmd_size(t_arg *arg);
int		init_list(t_arg_info *list, int index, t_info *info);
int		start_red(t_info *info, t_arg_info *list);
void	init(t_info *info);

/* PIPE */
int		create_pipe(t_info *info);
void	close_pipe(t_info *info);

/* REDIRECTION */
int		do_red(t_info *info, t_arg_info *list);
int		is_red(char *str, int quote);
void	check_close_fd(t_arg_info *list);
void	close_dup(t_info *info);
int		open_right_one(t_arg *arg, t_arg_info *list);

/* SIGNALS */
void	sig_ignore(int sig);
void	sig_reset(int sig);
void	exit_signal(t_info *info);
void	sig_int_set(int sig);
void	sig_set_heredoc(int sig);
void	sig_int_hdoc(int sig);
void	sig_set_fork(int sig);

/* TMP */
void	print_arg_list(t_arg *arg);
void	print_cmd_tab(t_info *info);

/* UTILITY */
void	add_string(char *str1, const char *str2);

/* WAIT */
void	wait_child(t_info *info);

# define TRUE 1
# define FALSE 2
# define ERROR -1
# define NAME_ONLY 1
# define EQUAL 2
# define VALUE 3
# define STDIN 0
# define STDOUT 1
# define NOPIPE 1

/* DEFINE FOR ENV */
# define ENV 1
# define EXPORT 2
# define PWD 1
# define SHLVL 2
# define OLDPWD 3

/* DEFINE FOR OPEN */
# define NOTHING 0
# define HEREDOC 3

#endif
