/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:36:48 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/17 11:03:55 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	co;
	size_t	co2;
	size_t	check_count;

	co = 0;
	co2 = 0;
	check_count = 0;
	if (needle[co2] == '\0')
		return ((char *)haystack);
	while (haystack[check_count] && check_count < len)
	{
		co2 = 0;
		co = check_count;
		while (needle[co2] && (haystack[co] == needle[co2]) && co < len)
		{
			co2++;
			co++;
		}
		if (needle[co2] == '\0')
			return ((char *)(haystack + check_count));
		check_count++;
	}
	return (NULL);
}
