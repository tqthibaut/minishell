/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:36:59 by jgao              #+#    #+#             */
/*   Updated: 2022/04/09 01:15:36 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	clearbuffer(char *buffer)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (buffer[i] != '\n')
		i++;
	i++;
	while (buffer[i])
		buffer[u++] = buffer[i++];
	buffer[u] = '\0';
}

static int	readbuffer(char *buffer, char **line)
{
	size_t	blen;
	size_t	llen;

	if (!buffer)
		return (-1);
	blen = custom_strlen(buffer);
	*line = ft_realloc(*line, blen);
	if (!*line)
		return (-2);
	llen = ft_strlen(*line);
	ft_memmove(*line + llen, buffer, blen);
	(*line)[llen + blen] = '\0';
	if (!buffer[blen])
	{
		buffer[0] = '\0';
		return (-1);
	}
	clearbuffer(buffer);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int				readret;
	int				ret;
	static char		buffer[256][BUFFER_SIZE + 1];

	ret = 0;
	readret = 1;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, buffer[fd], 0) < 0 || !line)
		return (-1);
	*line = NULL;
	while (readret > 0 && ret != 1)
	{
		ret = readbuffer(buffer[fd], line);
		if (ret == BUFFER_NULL)
		{
			readret = read(fd, buffer[fd], BUFFER_SIZE);
			if (readret < 0)
				return (-1);
			buffer[fd][readret] = '\0';
		}
		if (ret == MALLOC_ERROR)
			return (-1);
	}
	if (readret > 0)
		return (1);
	return (0);
}
