/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:20:27 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/15 19:27:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	count;
	char			*new_str;
	char			*check;

	count = 0;
	check = NULL;
	if (s && f)
	{
		new_str = ft_strnew(ft_strlen(s));
		check = new_str;
		if (new_str)
			while (*s)
			{
				*new_str++ = (*f)(count, *s++);
				count++;
			}
	}
	return (check);
}
