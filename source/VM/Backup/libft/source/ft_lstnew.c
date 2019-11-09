/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:04:30 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/19 10:10:22 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list *new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (!new_list)
		return (NULL);
	if (content == NULL)
	{
		(*new_list).content = NULL;
		(*new_list).content_size = 0;
	}
	else
	{
		(*new_list).content = ft_memalloc(content_size);
		if (!(*new_list).content)
		{
			ft_memdel((void **)&new_list);
			return (NULL);
		}
		(*new_list).content = ft_memcpy((*new_list).content, content,
			content_size);
		(*new_list).content_size = content_size;
	}
	(*new_list).next = NULL;
	return (new_list);
}
