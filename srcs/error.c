/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:24:19 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:18:32 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_next(int code, char *str)
{
	if (code == AMBIGUOUS)
	{
		ft_putstr_fd("Minishell: ambiguous redirect\n", 2);
		g_exit_status = 1;
		return (0);
	}
	if (code == IS_DIR)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Not a directory\n", 2);
		g_exit_status = 126;
	}
	if (code == PERMISSION)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_exit_status = 126;
	}
	return (ERROR);
}

int	print_error(int code, char *str)
{
	if (code == CMD_NOT_FOUND)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_status = 127;
	}
	if (code == MALLOC)
	{
		ft_putstr_fd("Malloc failed\n", 2);
		g_exit_status = 12;
	}
	if (code == FD_ERROR)
	{
		ft_putstr_fd("Dup error\n", 2);
		g_exit_status = 9;
	}
	if (code == SYNTAX)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token \'", 2);
		write(2, &str[0], 1);
		ft_putstr_fd("\'\n", 2);
		g_exit_status = 2;
	}
	return (print_next(code, str));
}
