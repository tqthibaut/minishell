/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:17:56 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:32:12 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_flag(t_info *info)
{
	if (info->current_list_arg->cmd[1][0] == '-')
	{
		ft_putstr_fd("Minishell: unset: ", 2);
		ft_putstr_fd(info->current_list_arg->cmd[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		if (info->current_list_arg->childpid != 0)
			g_exit_status = 2;
		return (TRUE);
	}
	return (FALSE);
}

void	child_unset(t_info *info)
{
	int	i;

	i = 1;
	if (!info->current_list_arg->cmd[1])
	{
		free_info(info);
		exit(0);
	}
	if (check_unset_flag(info) == TRUE)
	{
		free_info(info);
		exit(2);
	}
	while (info->current_list_arg->cmd[i])
	{
		find_and_unset(info->current_list_arg->cmd[i],
			info->list_env.exp, info);
		i++;
	}
	free_info(info);
	exit(0);
}
