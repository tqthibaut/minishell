/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:21:51 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 14:59:05 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_built_in(char *str)
{
	if (ft_strncmp(str, "exit", 5) == 0 || ft_strncmp(str, "pwd", 4) == 0
		|| ft_strncmp(str, "env", 4) == 0 || ft_strncmp(str, "export", 7) == 0
		|| ft_strncmp(str, "unset", 6) == 0 || ft_strncmp(str, "echo", 5) == 0
		|| ft_strncmp(str, "cd", 3) == 0)
		return (TRUE);
	return (FALSE);
}

int	go_to_built_in(t_info *info)
{
	close_pipe(info);
	if (ft_strncmp(info->current_list_arg->cmd[0], "exit", 5) == 0)
		return (built_in_exit(info));
	if (ft_strncmp(info->current_list_arg->cmd[0], "pwd", 4) == 0)
		return (built_in_pwd(info));
	if (ft_strncmp(info->current_list_arg->cmd[0], "env", 4) == 0)
		return (built_in_env(info));
	if (ft_strncmp(info->current_list_arg->cmd[0], "export", 7) == 0)
		return (built_in_export(info));
	if (ft_strncmp(info->current_list_arg->cmd[0], "unset", 6) == 0)
		return (built_in_unset(info));
	if (ft_strncmp(info->current_list_arg->cmd[0], "echo", 5) == 0)
		return (built_in_echo(info));
	if (ft_strncmp(info->current_list_arg->cmd[0], "cd", 3) == 0)
		return (built_in_cd(info));
	return (FALSE);
}
