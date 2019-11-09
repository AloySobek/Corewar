/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 12:39:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/19 12:55:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *res;

	res = NULL;
	while (*s)
		if (*s++ == (char)c)
			res = (char *)(s - 1);
	if ((char)c == '\0' && *s == '\0')
		res = (char *)s;
	return (res);
}
