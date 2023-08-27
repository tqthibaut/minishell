/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 12:07:11 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 22:45:06 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red(char *str, int quote)
{
	if ((ft_strncmp(str, ">", 2) == 0
			|| ft_strncmp(str, "<", 2) == 0
			|| ft_strncmp(str, ">>", 3) == 0
			|| ft_strncmp(str, "<<", 3) == 0)
		&& quote == FALSE)
		return (TRUE);
	return (FALSE);
}

int	open_right_one(t_arg *arg, t_arg_info *list)
{
	if (list->is_out == TRUE)
		close(list->outfilefd);
	if (arg->null == TRUE)
	{
		list->execute = FALSE;
		return (print_error(AMBIGUOUS, NULL));
	}
	list->outfilefd = open(arg->str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (list->outfilefd < 1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(arg->str);
		g_exit_status = 1;
		return (ERROR);
	}
	list->is_out = TRUE;
	return (0);
}
