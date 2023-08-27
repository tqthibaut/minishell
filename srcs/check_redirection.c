/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:44:17 by jgao              #+#    #+#             */
/*   Updated: 2022/04/04 14:08:42 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(char *buffer, int i)
{
	if (buffer[i] == '>')
	{
		if (buffer[i + 1] == '<')
			return (FALSE);
		return (TRUE);
	}
	if (buffer[i] == '<')
	{
		if (buffer[i + 1] == '>')
			return (FALSE);
		return (TRUE);
	}
	return (0);
}

static int	check_next_char(char *buffer, int i)
{
	if (buffer[i] == '>' || buffer[i] == '<' || buffer[i] == '|')
		return (ERROR);
	return (0);
}

int	check_redirection(char *buffer)
{
	int	i;
	int	save;

	i = 0;
	while (buffer[i])
	{
		if (is_redirection(buffer, i) == TRUE)
		{
			save = i;
			i++;
			if (buffer[i] == '>' || buffer[i] == '<')
				i++;
			while (buffer[i] == ' ')
				i++;
			if (!buffer[i])
				return (print_error(SYNTAX, &buffer[save]));
			if (check_next_char(buffer, i) == ERROR)
				return (print_error(SYNTAX, &buffer[i]));
		}
		else if (is_redirection(buffer, i) == FALSE)
			return (print_error(SYNTAX, &buffer[i]));
		i++;
	}
	return (0);
}
