/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:42:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/19 10:40:34 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int count;

	count = 0;
	while (s1[count] != '\0')
		count++;
	while (*s2 != '\0' && n)
	{
		s1[count++] = *s2++;
		n--;
	}
	s1[count] = '\0';
	return (s1);
}
