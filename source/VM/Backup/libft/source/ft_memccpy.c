/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 15:36:39 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/19 10:24:10 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void					*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*to;

	to = (unsigned char *)dst;
	while (n--)
	{
		*to++ = *(unsigned char *)src++;
		if (*(to - 1) == (unsigned char)c)
			return (to);
	}
	return (NULL);
}
