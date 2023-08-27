/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 11:55:14 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 22:35:39 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_right_two(t_arg *arg, t_arg_info *list)
{
	if (list->is_out == TRUE)
		close(list->outfilefd);
	if (arg->null == TRUE)
	{
		list->execute = FALSE;
		return (print_error(AMBIGUOUS, NULL));
	}
	list->outfilefd = open(arg->str, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (list->outfilefd < 1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(arg->str);
		g_exit_status = 1;
		return (ERROR);
	}
	list->is_out = TRUE;
	return (0);
}

static int	open_left_one(t_arg *arg, t_arg_info *list)
{
	if (list->is_in == TRUE || list->is_in == HEREDOC)
		close(list->infilefd);
	if (arg->null == TRUE)
	{
		list->execute = FALSE;
		return (print_error(AMBIGUOUS, NULL));
	}
	list->infilefd = open(arg->str, O_RDONLY);
	if (list->infilefd < 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		perror(arg->str);
		g_exit_status = 1;
		return (ERROR);
	}
	list->is_in = TRUE;
	return (0);
}

static int	hdoc_next(t_arg_info *list, t_info *info, int c_status, t_arg *arg)
{
	int	childpid;

	childpid = fork();
	if (childpid == 0)
	{
		static_magic(info);
		heredoc_read(list, arg->str, info);
	}
	sig_ignore(SIGINT);
	sig_ignore(SIGQUIT);
	waitpid(childpid, &c_status, WUNTRACED);
	if (WIFEXITED(c_status) == TRUE)
	{
		g_exit_status = WEXITSTATUS(c_status);
		if (g_exit_status == 130)
		{
			close_and_unlink(info);
			return (ERROR);
		}
	}
	close (list->infilefd);
	if (heredoc_open(list, 0) == ERROR)
		return (ERROR);
	return (0);
}

static int	open_left_two(t_arg *arg, t_arg_info *list, t_info *info)
{
	int	child_status;

	child_status = 0;
	if (find_quote(arg->str) == TRUE)
		list->heredoc_expansion = TRUE;
	else
		list->heredoc_expansion = FALSE;
	arg->str = remove_quotes(arg->str);
	if (!arg->str)
		return (ERROR);
	if (list->is_in == TRUE || list->is_in == HEREDOC)
		close(list->infilefd);
	list->is_in = HEREDOC;
	if (list->infile_name == NULL)
		if (heredoc_create_file(list, list->index) == ERROR)
			return (ERROR);
	if (heredoc_open(list, HEREDOC) == ERROR)
		return (ERROR);
	return (hdoc_next(list, info, child_status, arg));
}

int	do_red(t_info *info, t_arg_info *list)
{
	if (ft_strncmp(info->current_arg->str, ">", 2) == 0)
	{
		if (open_right_one(info->current_arg->next, list) == ERROR)
			return (ERROR);
	}
	else if (ft_strncmp(info->current_arg->str, "<", 2) == 0)
	{
		if (open_left_one(info->current_arg->next, list) == ERROR)
			return (ERROR);
	}
	else if (ft_strncmp(info->current_arg->str, ">>", 3) == 0)
	{
		if (open_right_two(info->current_arg->next, list) == ERROR)
			return (ERROR);
	}
	else if (ft_strncmp(info->current_arg->str, "<<", 3) == 0)
	{
		if (open_left_two(info->current_arg->next, list, info) == ERROR)
			return (ERROR);
	}
	return (0);
}
