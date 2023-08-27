/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:12:00 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 14:11:37 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	sizetab(long n, int b)
{
	int		count;

	count = 1;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n >= b)
	{
		n = n / b;
		count++;
	}
	return (count);
}

char	*ft_itoa_base(long nb, int b)
{
	char	*ret;
	size_t	i;
	int		len;
	char	*hexa;

	hexa = "0123456789abcdef";
	len = sizetab(nb, b);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
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
		ret[--i] = hexa[nb % b];
		nb = nb / b;
	}
	return (ret);
}
