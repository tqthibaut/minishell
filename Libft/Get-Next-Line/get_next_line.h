/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:31:50 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 11:58:48 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
size_t	lenbuffer(int fd);
size_t	ft_strlen(char *s);
size_t	custom_strlen(char *s);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t size);

# define BUFFER_NULL -1
# define MALLOC_ERROR -2

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

#endif
