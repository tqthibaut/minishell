/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:07:38 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 12:49:45 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_nbpipe(t_info *info)
{
	if (info->pipe.nbpipe > 0)
		info->current_list_arg->childpid = fork();
	else if (check_built_in(info->current_list_arg->cmd[0]) == FALSE)
		info->current_list_arg->childpid = fork();
	if (info->current_list_arg->childpid == 0)
	{
		sig_reset(SIGQUIT);
		sig_reset(SIGINT);
	}
	else
		sig_set_fork(SIGINT);
}

static void	do_dup(t_info *info)
{
	if (((info->current_list_arg->is_in == TRUE
				|| info->current_list_arg->is_out == TRUE)
			&& info->pipe.nbpipe == 0)
		|| info->current_list_arg->childpid == 0)
		which_dup(info);
}

static void	execute(t_info *info)
{
	if (info->current_list_arg->childpid != 0)
	{
		if (ft_strncmp(info->current_list_arg->cmd[0], "./minishell", 12) == 0)
			info->parent_status = FALSE;
	}
	if (info->pipe.nbpipe > 0)
	{
		if (info->current_list_arg->childpid == 0)
		{
			if (go_to_built_in(info) == FALSE)
				do_command(info);
		}
	}
	else
	{
		if (go_to_built_in(info) == FALSE
			&& info->current_list_arg->childpid == 0)
			do_command(info);
	}
}

static void	not_exec(t_info *info)
{
	if (info->current_list_arg->childpid == 0)
	{
		free_info(info);
		exit(0);
	}
}

int	command_part(t_info *info)
{
	info->current_list_arg = info->list_arg;
	create_pipe(info);
	free_null_tab(info);
	while (info->current_list_arg)
	{
		if (info->current_list_arg->cmd[0])
		{
			check_nbpipe(info);
			do_dup(info);
			if (info->current_list_arg->execute == TRUE)
				execute(info);
			else
				not_exec(info);
		}
		info->current_list_arg = info->current_list_arg->next;
	}
	close_pipe(info);
	if (info->parent_status == FALSE)
		sig_ignore(SIGINT);
	wait_child(info);
	close_and_unlink(info);
	return (0);
}
