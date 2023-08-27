/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 12:28:30 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 01:52:49 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	exit_arg(t_info *info)
{
	char	num;

	if (check_num(info->current_list_arg->cmd[1]) == TRUE)
	{
		num = atoi(info->current_list_arg->cmd[1]);
		free_info(info);
		printf("exit\n");
		g_exit_status = num;
		exit(num);
	}
	else
	{
		printf("exit\n");
		write(2, "minishell: exit: ", 17);
		write(2, info->current_list_arg->cmd[1],
			ft_strlen(info->current_list_arg->cmd[1]));
		write(2, ": numeric argument required\n", 28);
		free_info(info);
		g_exit_status = 2;
		exit(2);
	}
}

static void	exit_arg_child(t_info *info)
{
	char	num;

	if (check_num(info->current_list_arg->cmd[1]) == TRUE)
	{
		num = atoi(info->current_list_arg->cmd[1]);
		free_info(info);
		exit(num);
	}
	else
	{
		write(2, "minishell: exit: ", 17);
		write(2, info->current_list_arg->cmd[1],
			ft_strlen(info->current_list_arg->cmd[1]));
		write(2, ": numeric argument required\n", 28);
		free_info(info);
		exit(2);
	}
}

int	built_in_exit(t_info *info)
{
	if (info->current_list_arg->childpid == 0)
	{
		if (info->current_list_arg->cmd[1] == NULL)
		{
			free_info(info);
			exit(0);
		}
		else
			exit_arg_child(info);
	}
	if (info->current_list_arg->cmd[1] == NULL)
	{
		printf("exit\n");
		free_info(info);
		g_exit_status = 0;
		exit(0);
	}
	else
		exit_arg(info);
	return (FALSE);
}
