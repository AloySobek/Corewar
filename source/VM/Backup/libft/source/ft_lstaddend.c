/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 11:48:46 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/19 11:54:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *elem)
{
	t_list *list;

	list = NULL;
	if (alst && elem)
	{
		list = *alst;
		if (!list)
		{
			list = elem;
			(*list).next = NULL;
			return ;
		}
		while (list)
			list = (*list).next;
		list = elem;
		(*list).next = NULL;
	}
}
