/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:38:12 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/15 19:19:52 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *new_str;
	char *check;

	check = NULL;
	if (s && f)
	{
		new_str = ft_strnew(ft_strlen(s));
		check = new_str;
		if (new_str)
			while (*s)
				*new_str++ = (*f)(*s++);
	}
	return (check);
}
