/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:59:56 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 11:41:32 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sizetab(int nb)
{
	int		count;
	long	n;

	count = 1;
	n = nb;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ret;
	size_t	i;
	int		len;
	long	nb;

	len = sizetab(n);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	nb = n;
	if (nb < 0)
	{
		ret[0] = '-';
		nb = -nb;
	}
	i = len;
	ret[i] = '\0';
	if (nb == 0)
		ret[0] = '0';
	while (nb > 0)
	{
		ret[--i] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (ret);
}
