/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 10:54:21 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/18 20:01:03 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(const char *s1, const char *s2)
{
	char	*new_str;
	char	*check;

	check = NULL;
	if (s1 && s2)
	{
		new_str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		check = new_str;
		if (new_str)
		{
			while (*s1)
				*new_str++ = *s1++;
			while (*s2)
				*new_str++ = *s2++;
			*new_str = '\0';
		}
	}
	return (check);
}
