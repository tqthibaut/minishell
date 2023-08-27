/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:41:30 by jgao              #+#    #+#             */
/*   Updated: 2020/11/21 16:18:49 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	u;
	size_t	dlen;
	size_t	slen;

	i = 0;
	u = 0;
	slen = 0;
	while (src[slen])
		slen++;
	if (n == 0)
		return (slen);
	while (dest[u] && u < n)
		u++;
	if (dest[u] != '\0')
		return (slen + n);
	dlen = u;
	while (u < n - 1 && src[i])
		dest[u++] = src[i++];
	dest[u] = '\0';
	if (u + 1 > n)
		return (slen + n);
	return (dlen + slen);
}
