/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:35:28 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 11:42:52 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t len)
{
	void	*tab;
	size_t	i;

	i = 0;
	tab = malloc(len * nmemb);
	if (!tab)
		return (NULL);
	while (i < nmemb * len)
		((unsigned char *)tab)[i++] = '\0';
	return (tab);
}
