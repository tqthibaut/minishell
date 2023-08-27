/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:55:58 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 11:34:18 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static size_t	trimend(const char *s, const char *set, size_t i, size_t u)
{
	size_t	count;

	count = 0;
	while (set[u] && i > 0)
	{
		if (s[i] == set[u])
		{
			u = 0;
			i--;
			count++;
		}
		else
			u++;
	}
	return (count);
}

static size_t	trimstart(const char *s, const char *set, size_t i, size_t u)
{
	while (set[u])
	{
		if (s[i] == set[u])
		{
			u = 0;
			i++;
		}
		else
			u++;
	}
	return (i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	indret;
	char	*ret;
	size_t	len;

	indret = 0;
	if (set == NULL || s1 == NULL)
		return ((char *)s1);
	start = trimstart(s1, set, 0, 0);
	end = trimend(s1, set, my_strlen(s1) - 1, 0);
	len = my_strlen(s1);
	if (len == start)
		len = 0;
	else
		len = len - start - end;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	while (indret < len)
		ret[indret++] = s1[start++];
	ret[indret] = '\0';
	return (ret);
}
