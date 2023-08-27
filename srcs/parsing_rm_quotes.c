/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rm_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 14:37:14 by tthibaut          #+#    #+#             */
/*   Updated: 2022/04/08 23:51:32 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quote(char *delimiter, int i, int count)
{
	while (delimiter[i])
	{
		if (delimiter[i] == '\'')
		{
			i++;
			while (delimiter[i] != '\'')
				i++;
			count += 2;
			i++;
		}
		else if (delimiter[i] == '\"')
		{
			i++;
			while (delimiter[i] != '\"')
				i++;
			count += 2;
			i++;
		}
		if (delimiter[i] && delimiter[i] != '\'' && delimiter[i] != '\"')
			i++;
	}
	return (count);
}

static void	single_quote_fill(int *j, char *delimiter, int *i, char *new)
{
	(*j)++;
	while (delimiter[*j] && delimiter[*j] != '\'')
		new[(*i)++] = delimiter[(*j)++];
	if (delimiter[*j])
		(*j)++;
}

static void	double_quote_fill(int *j, int *i, char *delimiter, char *new)
{
	(*j)++;
	while (delimiter[*j] != '\"')
		new[(*i)++] = delimiter[(*j)++];
	if (delimiter[*j])
		(*j)++;
}

char	*remove_quotes_alloc(char *delimiter, int j)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(delimiter) - j + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (delimiter[j])
	{
		if (delimiter[j] == '\'')
			single_quote_fill(&j, delimiter, &i, new);
		if (delimiter[j] && delimiter[j] == '\"')
			double_quote_fill(&j, &i, delimiter, new);
		if (delimiter[j] && delimiter[j] != '\'' && delimiter[j] != '\"')
			new[i++] = delimiter[j++];
	}
	new[i] = '\0';
	free(delimiter);
	return (new);
}

char	*remove_quotes(char	*str)
{
	int		j;

	j = 0;
	j = count_quote(str, 0, 0);
	if (j == 0)
		return (str);
	str = remove_quotes_alloc(str, j);
	if (!str)
		return (NULL);
	return (str);
}
