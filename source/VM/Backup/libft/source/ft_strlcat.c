/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 16:11:39 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/18 20:01:37 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t dstlen;
	size_t srclen;
	size_t n;

	srclen = ft_strlen(src);
	if ((dstlen = ft_strlen(dst)) >= size)
		n = srclen + size;
	else
	{
		n = dstlen + srclen;
		while (*(src) != '\0' && dstlen < (size - 1))
		{
			*(dst + dstlen) = *(src++);
			dstlen++;
		}
		*(dst + dstlen) = '\0';
	}
	return (n);
}
