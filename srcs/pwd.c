/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 16:50:47 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:32:41 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_pwd(t_info *info)
{
	int		i;
	char	str[2048];

	i = 0;
	if (info->current_list_arg->cmd[1]
		&& info->current_list_arg->cmd[1][0] == '-')
	{
		ft_putstr_fd("Error: wrong option\n", 2);
		g_exit_status = 2;
		return (FALSE);
	}
	if (getcwd(str, 2048) == NULL)
	{
		ft_putstr_fd("Error: pwd failed\n", 2);
		g_exit_status = 1;
		return (FALSE);
	}
	printf("%s\n", str);
	if (info->current_list_arg->childpid == 0)
	{
		free_info(info);
		exit(0);
	}
	g_exit_status = 0;
	return (0);
}
