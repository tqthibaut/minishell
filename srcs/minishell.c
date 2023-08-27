/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:51:33 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 00:31:43 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	parsing_part(t_info *info)
{
	add_history(info->buffer);
	if (check_buffer(info) == ERROR)
		return (ERROR);
	if (split_arg(info) == ERROR)
	{
		reset_free(info);
		return (ERROR);
	}
	if (parse_cmd(info) == ERROR)
	{
		reset_free(info);
		return (ERROR);
	}
	return (0);
}

void	minishell(t_info *info)
{
	init(info);
	info->buffer = readline("minishell ");
	if (!info->buffer)
		exit_signal(info);
	if (info->buffer && info->buffer[0])
	{
		if (parsing_part(info) == ERROR)
		{
			reset_free(info);
			reset_dup(info);
			return ;
		}
		if (command_part(info) == ERROR)
		{
			reset_free(info);
			reset_dup(info);
			return ;
		}
	}
	reset_free(info);
	reset_dup(info);
}

int	main(int ac, char **av, char **env)
{
	t_info		info;

	if (ac > 1)
	{
		printf("Wrong number of arguments\n");
		av = av + 1;
		return (-1);
	}
	info.list_env.exp = init_env(env, EXPORT);
	info.list_env.envp = init_env(env, ENV);
	info.fdsave[0] = dup(STDIN);
	if (info.fdsave[0] == -1)
		return (print_error(FD_ERROR, NULL));
	info.fdsave[1] = dup(STDOUT);
	if (info.fdsave[1] == -1)
		return (print_error(FD_ERROR, NULL));
	while (1)
		minishell(&info);
	return (0);
}
