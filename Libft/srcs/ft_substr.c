/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 14:17:51 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 11:30:55 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
		i++;
	if (i <= start)
		len = 0;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	if (len == 0)
	{
		ret[0] = '\0';
		return (ret);
	}
	i = 0;
	while (s[start] && i < len)
		ret[i++] = s[start++];
	ret[i] = '\0';
	return (ret);
}
