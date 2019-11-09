/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 10:54:21 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/19 10:04:25 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnjoin(const char *s1, const char *s2, size_t n)
{
	char	*new_str;
	char	*check;

	check = NULL;
	if (s1 && s2)
	{
		new_str = ft_strnew(ft_strlen(s2) >= n ? n : ft_strlen(s2));
		check = new_str;
		if (new_str)
		{
			while (*s1)
				*new_str++ = *s1++;
			while (*s2 && n--)
				*new_str++ = *s2++;
			*new_str = '\0';
		}
	}
	return (check);
}
