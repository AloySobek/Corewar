/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 17:02:11 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/14 19:05:42 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char *dst_cp;

	dst_cp = dst;
	while (*src)
		*dst_cp++ = *src++;
	*dst_cp = '\0';
	return (dst);
}
