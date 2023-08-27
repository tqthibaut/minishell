/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str_next.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:43:24 by jgao              #+#    #+#             */
/*   Updated: 2021/01/12 14:22:20 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	my_count_word_split(const char *s, char *c, size_t i, int count)
{
	size_t	u;
	int		enter;
	int		firstsplit;

	enter = 0;
	firstsplit = 0;
	while (s[i])
	{
		u = 0;
		while (c[u] != s[i] && c[u])
			u++;
		if (s[i] == c[u] && enter == 0)
			count++;
		if (s[0] == c[u])
			firstsplit = 1;
		if (!c[u])
			enter = 0;
		else
			enter = 1;
		i++;
	}
	return (count - firstsplit - enter);
}

size_t	wordlen_split(const char *s, char *c, size_t i)
{
	size_t	count;
	size_t	u;

	count = 0;
	while (s[i])
	{
		u = 0;
		while (c[u])
		{
			if (s[i] == c[u])
				return (count);
			u++;
		}
		i++;
		count++;
	}
	return (count);
}
