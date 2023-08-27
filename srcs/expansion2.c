/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:46:41 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 18:24:09 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	total_exp_middle_part(char *str, int *i)
{
	if (str[*i] == '$' || ft_isdigit(str[*i]) == 1)
	{
		(*i)++;
		return (1);
	}
	while (str[*i] && str[*i] != ' ' && str[*i] != '\'' && str[*i] != '$'
		&& str[*i] != '\"' && str[*i] != '>'
		&& str[*i] != '<' && str[*i] != '|')
		(*i)++;
	return (0);
}

int	total_exp(char *str, int singleq, int doubleq, int count)
{
	int	i;

	i = 0;
	while (str[i])
	{
		check_current_quote(str[i], &singleq, &doubleq);
		if (str[i] == '$')
		{
			if (str[++i] == ' ' || !str[i] || str[i] == '>' || str[i] == '<'
				|| (doubleq == TRUE && str[i] == '\"'))
				continue ;
			if (singleq == FALSE)
				count++;
			if (total_exp_middle_part(str, &i) == 1)
				continue ;
		}
		else
			i++;
	}
	return (count);
}

int	find_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	replace_quote_tab(char **replace_exp)
{
	int	i;
	int	u;

	i = 0;
	while (replace_exp[i])
	{
		u = 0;
		while (replace_exp[i][u])
		{
			if (replace_exp[i][u] == '\'')
				replace_exp[i][u] = -1;
			if (replace_exp[i][u] == '\"')
				replace_exp[i][u] = -2;
			u++;
		}
		i++;
	}
}

char	*content_exp(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	if (str)
		ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	else
		ret = malloc(sizeof(char) * 1);
	if (!ret)
		return (NULL);
	if (str)
	{
		while (str[i])
		{
			ret[i] = str[i];
			i++;
		}
	}
	ret[i] = '\0';
	return (ret);
}
