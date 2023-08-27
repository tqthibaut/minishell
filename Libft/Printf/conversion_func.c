/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:39:29 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 14:17:13 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_putnbr_octal(t_tab *tab)
{
	char	*str;
	int		len;
	int		write_len;

	str = ft_itoa_base(tab->uintnb, 8);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	write_len = print_argint(tab, str, len);
	free(str);
	return (write_len);
}

int	ft_putnbr_unsigned(t_tab *tab)
{
	char	*str;
	int		len;
	int		write_len;

	str = ft_itoa_base(tab->uintnb, 10);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	write_len = print_argint(tab, str, len);
	free(str);
	return (write_len);
}

int	ft_putnbr_hexa(t_tab *tab)
{
	char	*str;
	int		len;
	int		write_len;

	str = ft_itoa_base(tab->uintnb, 16);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	write_len = print_argint(tab, str, len);
	free(str);
	return (write_len);
}

int	ft_putnbr_hexa_up(t_tab *tab)
{
	char	*str;
	int		len;
	int		i;
	int		write_len;

	i = 0;
	str = ft_itoa_base(tab->uintnb, 16);
	if (!str)
		return (-1);
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'f')
			str[i] = str[i] - 32;
		i++;
	}
	write_len = print_argint(tab, str, len);
	free(str);
	return (write_len);
}
