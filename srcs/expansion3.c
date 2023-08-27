/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 16:56:03 by jgao              #+#    #+#             */
/*   Updated: 2022/04/08 18:11:27 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_current_quote(char c, int *singleq, int *doubleq)
{
	if (c == '\'' && *singleq == TRUE)
		*singleq = FALSE;
	else if (c == '\'' && *doubleq == FALSE)
		*singleq = TRUE;
	if (c == '\"' && *doubleq == TRUE)
		*doubleq = FALSE;
	else if (c == '\"' && *singleq == FALSE)
		*doubleq = TRUE;
}

static int	find_len_exp(int *i, char *str, int *singleq, int *doubleq)
{
	if (str[++(*i)] == '\"' && *doubleq == TRUE)
		return (-2);
	if (*singleq == FALSE)
	{
		if (str[*i] == '?')
			return (-3);
		if (str[*i] == ' ' || !str[*i] || str[*i] == '>' || str[*i] == '<')
			return (-2);
		return (length_exp(str, *i));
	}
	return (0);
}

static char	*exit_value(void)
{
	char	*exit_status;
	char	*ret;

	exit_status = ft_itoa(g_exit_status);
	if (!exit_status)
	{
		print_error(MALLOC, NULL);
		return (NULL);
	}
	ret = content_exp(exit_status);
	free(exit_status);
	return (ret);
}

static char	*find_env_char(t_env *env, int *i, int exp_length, char *str)
{
	while (env)
	{
		if (ft_strncmp(&str[*i], env->str, exp_length) == 0)
			if (env->str[exp_length] == '=')
				return (content_exp(&env->str[exp_length + 1]));
		env = env->next;
	}
	if (str[*i] == '$')
		(*i)++;
	return (content_exp(NULL));
}

char	*find_exp(char *str, int *i, t_env *env, int *doubleq)
{
	int		exp_length;
	int		ret_val;
	int		singleq;

	singleq = FALSE;
	exp_length = 0;
	while (str[*i])
	{
		check_current_quote(str[*i], &singleq, doubleq);
		if (str[*i] == '$')
		{
			ret_val = find_len_exp(i, str, &singleq, doubleq);
			if (ret_val == -2)
				continue ;
			if (ret_val == ERROR)
				return (NULL);
			if (ret_val == -3)
				return (exit_value());
			if (ret_val > 0)
				break ;
		}
		(*i)++;
	}
	exp_length = ret_val;
	return (find_env_char(env, i, exp_length, str));
}
