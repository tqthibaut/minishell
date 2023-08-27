/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:15:50 by jgao              #+#    #+#             */
/*   Updated: 2022/04/01 15:42:02 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_before_pipe(char *buffer, int i)
{
	i--;
	while (buffer[i] == ' ')
		i--;
	if (i < 0)
		return (ERROR);
	if (buffer[i] == '|' || buffer[i] == '<' || buffer[i] == '>')
		return (ERROR);
	return (0);
}

static int	check_after_pipe(char *buffer, int i)
{
	i++;
	while (buffer[i] == ' ')
		i++;
	if (!buffer[i])
		return (ERROR);
	if (buffer[i] == '|')
		return (ERROR);
	return (0);
}

int	check_pipe(char *buffer)
{
	int	i;

	i = 0;
	if (buffer[0] == '|')
		return (print_error(SYNTAX, buffer));
	while (buffer[i])
	{
		if (buffer[i] == '|')
		{
			if (i > 0 && check_before_pipe(buffer, i) == ERROR)
				return (print_error(SYNTAX, &buffer[i]));
			if (check_after_pipe(buffer, i) == ERROR)
				return (print_error(SYNTAX, &buffer[i]));
		}
		i++;
	}
	return (0);
}
