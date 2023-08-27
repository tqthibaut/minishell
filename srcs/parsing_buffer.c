/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:49:09 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:43:13 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_token_quote(char *buffer, int *i)
{
	if (buffer[*i] == '\'')
	{
		(*i)++;
		while (buffer[*i])
			if (buffer[(*i)++] == '\'')
				return (1);
	}
	if (buffer[*i] == '\"')
	{
		(*i)++;
		while (buffer[*i])
			if (buffer[(*i)++] == '\"')
				return (1);
	}
	return (0);
}

static int	check_token(char *buffer)
{
	int	i;

	i = 0;
	if (!buffer)
		return (0);
	while (buffer[i])
	{
		if (check_token_quote(buffer, &i) == 1)
			break ;
		if (buffer[i] == '&' || buffer[i] == ';' || buffer[i] == '('
			|| buffer[i] == ')' || buffer[i] == '~')
			return (print_error(SYNTAX, &buffer[i]));
		if (buffer[i])
			i++;
	}
	return (0);
}

static int	check_quote(char *buffer)
{
	int		i;
	char	save;

	save = '\0';
	i = 0;
	while (buffer[i])
	{
		if ((buffer[i] == '\'' || buffer[i] == '\"') && save == '\0')
			save = buffer[i];
		else if (buffer[i] == save)
			save = '\0';
		i++;
	}
	if (save != '\0')
		return (print_error(SYNTAX, &save));
	return (0);
}

int	check_buffer_full_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (!str[i])
		return (ERROR);
	return (0);
}

int	check_buffer(t_info *info)
{
	int		i;
	char	*new_buffer;

	i = 0;
	if (check_buffer_full_space(info->buffer) == ERROR)
		return (ERROR);
	if (check_quote(info->buffer) == ERROR)
		return (ERROR);
	if (check_token(info->buffer) == ERROR)
		return (ERROR);
	if (check_redirection(info->buffer) == ERROR)
		return (ERROR);
	if (check_pipe(info->buffer) == ERROR)
		return (ERROR);
	new_buffer = realloc_parsing_space(info->buffer, 0, 0, '\0');
	if (!new_buffer)
		return (print_error(MALLOC, NULL));
	if (new_buffer != info->buffer)
	{
		free(info->buffer);
		info->buffer = new_buffer;
	}
	return (0);
}
