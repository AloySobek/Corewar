/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:24:10 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/16 18:54:15 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int count;
	int count2;
	int check_count;

	count = 0;
	count2 = 0;
	check_count = 0;
	if (needle[count] == '\0')
		return ((char *)haystack);
	while (haystack[check_count])
	{
		count2 = 0;
		count = check_count;
		while (needle[count2] && (haystack[count] == needle[count2]))
		{
			count++;
			count2++;
		}
		if (needle[count2] == '\0')
			return ((char *)(haystack + check_count));
		check_count++;
	}
	return (NULL);
}
