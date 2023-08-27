/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tthibaut <tthibaut@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 15:36:59 by jgao              #+#    #+#             */
/*   Updated: 2022/04/04 12:20:38 by tthibaut         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	my_count_word(const char *s, char c)
{
	size_t	i;
	size_t	count;
	int		enter;

	i = 0;
	count = 1;
	enter = 0;
	while (s[i] == c && s[i])
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
			enter = 1;
		}
		if (enter == 1 && s[i] != '\0')
			count++;
		if (enter == 0)
			i++;
		enter = 0;
	}
	return (count);
}

static size_t	wordlen(const char *s, char c, size_t i)
{
	size_t	count;
	size_t	firstind;

	count = 0;
	firstind = i;
	while (s[i])
	{
		if (s[i] == c && i != firstind)
			return (count);
		i++;
		count++;
	}
	return (count);
}

static int	ft_freetab(char ***tab)
{
	size_t	ind;

	ind = 0;
	if (*tab)
	{
		while ((*tab)[ind])
		{
			free((*tab)[ind]);
			(*tab)[ind++] = NULL;
		}
		free(*tab);
		*tab = NULL;
	}
	return (0);
}

static char	**ft_split_next(const char *s, char c, char **tab, size_t nbw)
{
	size_t	indtab;
	size_t	i;
	size_t	u;

	u = 0;
	indtab = 0;
	i = 0;
	while (s[i] && s[i] == c)
		i++;
	while (indtab < nbw)
	{
		tab[indtab] = malloc(sizeof(char) * (wordlen(s, c, i) + 1));
		if (!tab[indtab])
			if (ft_freetab(&tab) == 0)
				return (NULL);
		while (s[i] && s[i] != c)
			tab[indtab][u++] = s[i++];
		tab[indtab][u] = '\0';
		u = 0;
		indtab++;
		while (s[i] && s[i] == c)
			i++;
	}
	tab[indtab] = NULL;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	size_t	nbword;
	char	**tab;

	if (s == NULL)
		return (NULL);
	nbword = my_count_word(s, c);
	tab = malloc(sizeof(char *) * (nbword + 1));
	if (!tab)
		return (NULL);
	return (ft_split_next(s, c, tab, nbword));
}
