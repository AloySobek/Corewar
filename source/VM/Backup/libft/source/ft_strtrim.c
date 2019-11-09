/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:34:26 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/16 14:13:43 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(const char *s)
{
	char	*new_str;
	char	*check;
	size_t	i;

	i = 0;
	check = NULL;
	if (s)
	{
		while (*s == ' ' || *s == '\n' || *s == '\t')
			s++;
		while (s[i])
			i++;
		if (i > 0)
			i--;
		while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && i > 0)
			i--;
		new_str = ft_strnew(i++ + 1);
		if ((check = new_str))
		{
			while (*s && i--)
				*new_str++ = *s++;
			*new_str = '\0';
		}
	}
	return (check);
}
