/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 16:02:52 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 23:46:43 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	hdoc_exp(char *buffer, t_info *info)
{
	buffer = replace_expansion(info, buffer);
	if (!buffer)
	{
		ft_putstr_fd("Erreur Malloc\n", 2);
		free_all_with_unlink(NULL);
		exit(2);
	}
}

static void	hdoc_reading(char *buf, char *del, t_info *info, t_arg_info *list)
{
	while (1)
	{
		buf = readline("> ");
		if (buf == NULL || !ft_strncmp(buf, del, ft_strlen(buf) + 1))
		{
			if (buf == NULL)
			{
				printf("Command terminated with EOF, wanted \"%s\"\n", del);
				rl_redisplay();
			}
			break ;
		}
		if (list->heredoc_expansion == TRUE)
			hdoc_exp(buf, info);
		write(list->infilefd, buf, ft_strlen(buf));
		write(list->infilefd, "\n", 1);
		free(buf);
		buf = NULL;
	}
}

void	heredoc_read(t_arg_info *list, char *delimiter, t_info *info)
{
	char	*buffer;

	buffer = NULL;
	sig_ignore(SIGQUIT);
	sig_set_heredoc(SIGINT);
	if (count_quote(delimiter, 0, 0) > 0)
	{
		list->heredoc_expansion = FALSE;
		delimiter = remove_quotes(delimiter);
		if (!delimiter)
		{
			ft_putstr_fd("Erreur Malloc\n", 2);
			free_all_with_unlink(info);
			exit(130);
		}
	}
	else
		list->heredoc_expansion = TRUE;
	hdoc_reading(buffer, delimiter, info, list);
	close(list->infilefd);
	free_info(info);
	exit(0);
}

int	heredoc_open(t_arg_info *list, int type)
{
	if (type == HEREDOC)
		list->infilefd = open(list->infile_name,
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		list->infilefd = open(list->infile_name, O_RDONLY);
	if (list->infilefd == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		perror(list->infile_name);
		return (ERROR);
	}
	return (0);
}
