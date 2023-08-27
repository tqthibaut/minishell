/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 17:39:23 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 18:25:39 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_next(int *i, int doubleq, char *str, int *count)
{
	if (doubleq == TRUE && str[*i] == '\"')
		return (1);
	if (str[*i] == ' ' || !str[*i] || str[*i] == '>' || str[*i] == '<')
	{
		if (str[*i] == ' ')
			(*i)++;
		return (1);
	}
	(*count)++;
	if (str[*i] == '$' || str[*i] == '?' || ft_isdigit(str[*i]) == 1)
	{
		(*i)++;
		(*count)++;
	}
	else
	{
		while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '$'
			&& str[*i] != '\"' && str[*i] != '>'
			&& str[*i] != '<' && str[*i] != '|')
		{
			(*i)++;
			(*count)++;
		}
	}
	return (0);
}

int	count_exp_word_remove(char *str)
{
	int	i;
	int	count;
	int	singleq;
	int	doubleq;

	i = 0;
	count = 0;
	singleq = FALSE;
	doubleq = FALSE;
	while (str[i])
	{
		check_current_quote(str[i], &singleq, &doubleq);
		if (singleq == FALSE)
		{
			if (str[i++] == '$')
			{
				if (count_next(&i, doubleq, str, &count) == 1)
					continue ;
			}
		}
		else
			i++;
	}
	return (count);
}
