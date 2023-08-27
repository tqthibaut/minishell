/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:40:37 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 02:28:17 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		if (str[i++] == '=')
			return (ENV);
	return (EXPORT);
}

static int	check_exp(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != ';')
	{
		if (ft_isalnum(str[i++]) == 0)
			return (FALSE);
	}
	if (ft_isdigit(str[0]) != 0)
		return (FALSE);
	return (TRUE);
}

static int	exporting(t_info *info)
{
	int		i;
	int		num;

	i = 1;
	num = 0;
	while (info->current_list_arg->cmd[i])
	{
		if (check_exp(info->current_list_arg->cmd[i]) == FALSE)
		{
			num = 1;
			ft_putstr_fd("Minishell: export: ", 2);
			ft_putstr_fd(info->current_list_arg->cmd[i++], 2);
			ft_putstr_fd(": Not a valid identifier\n", 2);
			continue ;
		}
		if (check_equal(info->current_list_arg->cmd[i]) == ENV)
		{
			add_export(info, info->current_list_arg->cmd[i]);
			add_env(info, info->current_list_arg->cmd[i]);
		}
		else
			add_export(info, info->current_list_arg->cmd[i]);
		i++;
	}
	return (num);
}

int	built_in_export(t_info *info)
{
	int	num;

	if (info->current_list_arg->childpid == 0)
	{
		if (!info->current_list_arg->cmd[1])
		{
			print_list(info->list_env.exp);
			free_info(info);
			exit(0);
		}
		else
			num = exporting(info);
		free_info(info);
		exit(num);
	}
	if (!info->current_list_arg->cmd[1])
	{
		print_list(info->list_env.exp);
		g_exit_status = 0;
		return (0);
	}
	else
		num = exporting(info);
	g_exit_status = num;
	return (0);
}
