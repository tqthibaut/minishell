/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:58:04 by jgao              #+#    #+#             */
/*   Updated: 2021/12/20 14:40:48 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (i < n && ((unsigned char *)dest)[i] && dest != src + i)
			i++;
		if (i < n && dest == src + i)
		{
			while (0 < n--)
				((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
			return (dest);
		}
	}
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	custom_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*ret;
	size_t	i;
	size_t	len;

	i = 0;
	if (ptr == NULL)
		len = 0;
	else
		len = ft_strlen(ptr);
	ret = malloc(sizeof(ptr) * (len + size + 1));
	if (!ret)
		return (NULL);
	if (ptr == NULL)
	{
		((unsigned char *)ret)[0] = '\0';
		return (ret);
	}
	while (((unsigned char *)ptr)[i])
	{
		((unsigned char *)ret)[i] = ((unsigned char *)ptr)[i];
		i++;
	}
	((unsigned char *)ret)[i] = '\0';
	free(ptr);
	return (ret);
}
