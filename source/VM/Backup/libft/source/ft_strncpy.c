/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:08:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/19 10:37:58 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *dst_cp;

	dst_cp = dst;
	while (*src && len)
	{
		*dst_cp++ = *src++;
		len--;
	}
	while (len--)
		*dst_cp++ = '\0';
	return (dst);
}
