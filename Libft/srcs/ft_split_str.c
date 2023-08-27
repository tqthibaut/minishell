/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:36:59 by jgao              #+#    #+#             */
/*   Updated: 2021/01/12 14:23:25 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_freetab(char **tab, size_t i)
{
	size_t	ind;

	ind = 0;
	while (ind < i)
		free(tab[ind++]);
	free(tab);
	return (0);
}

static int	find_next_word(const char *s, char *c, size_t i)
{
	size_t	u;

	u = 0;
	while (c[u])
	{
		if (s[i] == c[u])
		{
			i++;
			u = 0;
		}
		else
			u++;
	}
	return (i);
}

static size_t	fill_tab(const char *s, char *c, char *tab, size_t i)
{
	size_t	u;
	size_t	indtab;

	u = 0;
	indtab = 0;
	while (s[i] != c[u] && s[i])
	{
		u++;
		if (!c[u])
		{
			tab[indtab++] = s[i++];
			u = 0;
		}
	}
	tab[indtab] = '\0';
	return (i);
}

static char	**ft_split_next(const char *s, char *c, char **tab, size_t nbw)
{
	size_t	indtab;
	size_t	i;

	indtab = 0;
	i = find_next_word(s, c, 0);
	while (indtab < nbw)
	{
		tab[indtab] = malloc(sizeof(char) * (wordlen_split(s, c, i) + 1));
		if (!tab[indtab])
			if (ft_freetab(tab, indtab) == 0)
				return (NULL);
		i = fill_tab(s, c, tab[indtab++], i);
		i = find_next_word(s, c, i + 1);
	}
	tab[indtab] = NULL;
	return (tab);
}

char	**ft_split_str(const char *s, char *c)
{
	size_t	nbword;
	char	**tab;

	if (s == NULL)
		return (NULL);
	nbword = my_count_word_split(s, c, 0, 1);
	tab = malloc(sizeof(char *) * (nbword + 1));
	if (!tab)
		return (NULL);
	return (ft_split_next(s, c, tab, nbword));
}
