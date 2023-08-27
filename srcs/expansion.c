/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:19:45 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 18:04:36 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	length_exp(char *str, int i)
{
	int	count;

	count = 0;
	if (str[i] == '$' || ft_isdigit(str[i]) == 1)
		return (count + 1);
	while (str[i] && str[i] != ' ' && str[i] != '\'' && str[i] != '$'
		&& str[i] != '\"' && str[i] != '>' && str[i] != '<' && str[i] != '|')
	{
		i++;
		count++;
	}
	return (count);
}

char	**fill_replace_tab(t_info *info, char *str, int i, int u)
{
	int		total_word;
	char	**ret;
	int		singleq;
	int		doubleq;

	singleq = FALSE;
	doubleq = FALSE;
	total_word = total_exp(str, FALSE, FALSE, 0);
	ret = malloc(sizeof(char *) * (total_word + 1));
	while (i < total_word)
	{
		ret[i] = find_exp(str, &u, info->list_env.envp, &doubleq);
		if (!ret[i++])
		{
			while (--i >= 0)
				free(ret[i--]);
			free(ret);
			return (NULL);
		}
	}
	ret[i] = NULL;
	return (ret);
}

void	fill_ret(char *str, char *ret, char **replace_exp, t_index_exp *index)
{
	index->i++;
	if (!str[index->i] || str[index->i] == ' ' || str[index->i] == '<'
		|| str[index->i] == '>' || (str[index->i] == '\"'
			&& index->doubleq == TRUE))
	{
		ret[index->u++] = str[index->i - 1];
		return ;
	}
	index->word_tab = 0;
	if (replace_exp[index->ind_tab])
		while (replace_exp[index->ind_tab][index->word_tab])
			ret[index->u++] = replace_exp[index->ind_tab][index->word_tab++];
	index->ind_tab++;
	if (str[index->i] == '?' || str[index->i] == '$'
		|| ft_isdigit(str[index->i]) == 1)
	{
		index->i++;
		return ;
	}
	while (str[index->i] && str[index->i] != ' ' && str[index->i] != '\''
		&& str[index->i] != '$' && str[index->i] != '\"'
		&& str[index->i] != '>' && str[index->i] != '<' && str[index->i] != '|')
		index->i++;
}

char	*replace_buffer(char **replace_exp, int nb_rm_exp, char *str, int size)
{
	char		*ret;
	t_index_exp	index;

	index.i = 0;
	index.u = 0;
	index.ind_tab = 0;
	index.singleq = FALSE;
	index.doubleq = FALSE;
	ret = malloc(sizeof(char) * (ft_strlen(str) + size - nb_rm_exp + 1));
	if (!ret)
		return (NULL);
	while (str[index.i])
	{
		check_current_quote(str[index.i], &index.singleq, &index.doubleq);
		if (str[index.i] == '$' && index.singleq == FALSE)
			fill_ret(str, ret, replace_exp, &index);
		else
			ret[index.u++] = str[index.i++];
	}
	ret[index.u] = '\0';
	return (ret);
}

char	*replace_expansion(t_info *info, char *str)
{
	char	*ret;
	char	**replace_exp;
	int		nb_rm_exp;
	int		size_replace;
	int		i;

	i = 0;
	size_replace = 0;
	nb_rm_exp = count_exp_word_remove(str);
	if (nb_rm_exp == 0)
		return (str);
	replace_exp = fill_replace_tab(info, str, 0, 0);
	if (!replace_exp)
		return (NULL);
	replace_quote_tab(replace_exp);
	while (replace_exp[i])
		size_replace += ft_strlen(replace_exp[i++]);
	ret = replace_buffer(replace_exp, nb_rm_exp, str, size_replace);
	if (!ret)
		return (NULL);
	tab_free(&replace_exp);
	free(str);
	return (ret);
}
