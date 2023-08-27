/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:41:04 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 11:35:32 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (i);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	u;
	char	*ret;

	i = 0;
	u = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	ret = malloc(sizeof(char) * (my_strlen(s1) + my_strlen(s2) + 1));
	if (!ret)
		return (NULL);
	if (s1 != NULL)
		while (s1[i])
			ret[u++] = s1[i++];
	i = 0;
	if (s2 != NULL)
		while (s2[i])
			ret[u++] = s2[i++];
	ret[u] = '\0';
	return (ret);
}
