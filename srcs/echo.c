/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:50:08 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 22:44:01 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_option(t_info *info, int i)
{
	t_arg_info	*arg;

	arg = info->current_list_arg;
	while (arg->cmd[i])
	{
		printf("%s", arg->cmd[i++]);
		if (arg->cmd[i])
			printf(" ");
	}
}

static void	print_echo(t_info *info, int i)
{
	t_arg_info	*arg;

	arg = info->current_list_arg;
	while (arg->cmd[i])
	{
		printf("%s", arg->cmd[i++]);
		if (arg->cmd[i])
			printf(" ");
	}
	printf("\n");
}

static int	check_flag(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		if (str[i++] == '-')
		{
			while (str[i] == 'n')
				i++;
			if (!str[i])
				return (TRUE);
		}
	}
	return (FALSE);
}

static int	do_echo(t_info *info, int i)
{
	if (info->current_list_arg->cmd[i])
	{
		if (check_flag(info->current_list_arg->cmd[1]) == TRUE)
		{
			while (check_flag(info->current_list_arg->cmd[i]) == TRUE)
					i++;
			print_option(info, i);
		}
		else
			print_echo(info, i);
	}
	else
		printf("\n");
	return (0);
}

int	built_in_echo(t_info *info)
{
	int	i;

	i = 1;
	if (info->current_list_arg->childpid == 0)
	{
		do_echo(info, i);
		free_info(info);
		exit(0);
	}
	do_echo(info, i);
	g_exit_status = 0;
	return (0);
}
