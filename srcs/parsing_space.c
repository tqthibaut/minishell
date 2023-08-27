/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:52:23 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 21:38:02 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pipe_red(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

static int	count_next(int i, char *buffer, int count)
{
	if (i > 0 && buffer[i - 1] != ' '
		&& is_pipe_red(buffer[i - 1]) == 0)
		count++;
	if (buffer[i] == '|' || (buffer[i + 1] != ' '
			&& is_pipe_red(buffer[i + 1]) == 0))
		count++;
	return (count);
}

static int	count_space_need(char *buffer)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	quote = '\0';
	while (buffer[i])
	{
		if ((buffer[i] == '\'' || buffer[i] == '\"') && quote == '\0')
			quote = buffer[i];
		else if (quote == buffer[i])
			quote = '\0';
		if (is_pipe_red(buffer[i]) == 1)
			if (quote == '\0')
				count = count_next(i, buffer, count);
		i++;
	}
	return (count);
}

static int	in_parsing(char *buffer, int *i, int *u, char *ret)
{
	if (is_pipe_red(buffer[*i]) == 1)
	{
		if (*i > 0 && buffer[*i - 1] != ' '
			&& is_pipe_red(buffer[*i - 1]) == 0)
		{
			ret[(*u)++] = ' ';
			ret[*u] = buffer[*i];
		}
		if (buffer[*i] == '|' || (buffer[*i + 1] != ' '
				&& is_pipe_red(buffer[*i + 1]) == 0))
			ret[++(*u)] = ' ';
	}
	return (0);
}

char	*realloc_parsing_space(char *buffer, int i, int u, char quote)
{
	char	*ret;
	int		nb;

	nb = count_space_need(buffer);
	if (nb != 0)
		ret = malloc(sizeof(char) * (ft_strlen(buffer) + nb + 1));
	else
		return (buffer);
	if (!ret)
		return (NULL);
	while (buffer[i])
	{
		if ((buffer[i] == '\'' || buffer[i] == '\"') && quote == '\0')
			quote = buffer[i];
		else if (quote == buffer[i])
			quote = '\0';
		ret[u] = buffer[i];
		if (quote == '\0')
			in_parsing(buffer, &i, &u, ret);
		u++;
		i++;
	}
	ret[u] = '\0';
	return (ret);
}
