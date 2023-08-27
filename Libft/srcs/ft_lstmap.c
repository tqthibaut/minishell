/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgao <jgao@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 12:28:17 by jgao              #+#    #+#             */
/*   Updated: 2021/01/08 11:41:06 by jgao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	my_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while ((*lst))
	{
		tmp = &**lst;
		(*del)(tmp->content);
		(*lst) = (*lst)->next;
		free(tmp);
	}
}

static void	my_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*start;

	start = NULL;
	while (lst)
	{
		ret = malloc(sizeof(t_list));
		if (!ret)
		{
			my_lstclear(&start, (del));
			return (NULL);
		}
		ret->content = (*f)(lst->content);
		ret->next = NULL;
		lst = lst->next;
		my_lstadd_back(&start, ret);
	}
	return (start);
}
