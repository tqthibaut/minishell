/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 00:53:01 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 12:46:57 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_error(t_info *info, int ret_stat, struct stat info_cmd)
{
	ret_stat = stat(info->current_list_arg->cmd[0], &info_cmd);
	if (S_ISDIR(info_cmd.st_mode))
	{
		print_error(IS_DIR, info->current_list_arg->cmd[0]);
		free_info(info);
		exit(126);
	}
	else if (S_IXUSR && info_cmd.st_mode)
	{
		print_error(PERMISSION, info->current_list_arg->cmd[0]);
		free_info(info);
		exit(126);
	}
	print_error(CMD_NOT_FOUND, info->current_list_arg->cmd[0]);
	free_info(info);
	exit(127);
}

int	do_command(t_info *info)
{
	struct stat	info_cmd;
	int			ret_stat;

	sig_reset(SIGQUIT);
	sig_reset(SIGINT);
	info_cmd.st_mode = 0;
	ret_stat = 0;
	if (info->current_list_arg->childpid == 0)
	{
		if (!info->current_list_arg->cmd[0])
		{
			free_info(info);
			exit(0);
		}
		if (execve(info->current_list_arg->cmd[0],
				&info->current_list_arg->cmd[0], info->list_env.tab_env) == -1)
			handle_error(info, ret_stat, info_cmd);
	}
	return (0);
}
