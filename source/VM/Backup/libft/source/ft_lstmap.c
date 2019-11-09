/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:27:25 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/19 11:16:29 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	clean_memory(t_list *inter_list, t_list *new_list)
{
	while (inter_list)
	{
		new_list = (*inter_list).next;
		free(inter_list);
		inter_list = new_list;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_list;
	t_list	*inter_list;

	new_list = NULL;
	inter_list = NULL;
	if (lst && f)
	{
		new_list = (*f)(lst);
		if (!new_list)
			return (NULL);
		inter_list = new_list;
		lst = (*lst).next;
		while (lst)
		{
			(*new_list).next = (*f)(lst);
			if (!(*new_list).next)
			{
				clean_memory(inter_list, new_list);
				return (NULL);
			}
			new_list = (*new_list).next;
			lst = (*lst).next;
		}
	}
	return (inter_list);
}
