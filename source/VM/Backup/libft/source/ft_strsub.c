/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 19:44:53 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/15 20:13:01 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	char	*check;

	check = NULL;
	if (s && ((ft_strlen(s) - start) >= len))
	{
		new_str = ft_strnew(len);
		check = new_str;
		if (new_str)
		{
			s = s + start;
			while (*s && len--)
				*new_str++ = *s++;
		}
	}
	return (check);
}
