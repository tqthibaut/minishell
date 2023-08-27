/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 18:29:57 by jgao              #+#    #+#             */
/*   Updated: 2020/11/23 19:39:15 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	u;

	i = 0;
	u = 0;
	if (s2[0] == 0)
		return ((char *)s1);
	while (i < len && s1[i])
	{
		while (s1[i + u] == s2[u] && i + u < len && s1[i + u])
			u++;
		if (s2[u] == '\0')
			return ((char *)s1 + i);
		u = 0;
		i++;
	}
	return (NULL);
}
