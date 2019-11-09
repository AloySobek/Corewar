/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcreate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 19:41:43 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/19 17:30:58 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcrop(char *str, char c)
{
	char *new_str;
	char *check;

	while (*str && *str != c)
		str++;
	if (*str == c)
		str++;
	if (!(new_str = ft_strnew(ft_strlen(str))))
		return (NULL);
	check = new_str;
	while (*str)
		*new_str++ = *str++;
	return (check);
}
