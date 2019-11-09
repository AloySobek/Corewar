/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 12:00:18 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/22 20:27:32 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcut(char *str, char c)
{
	char	*str_new;
	char	*check;

	if (!(str_new = ft_strnew(ft_strclen(str, c))))
		return (NULL);
	check = str_new;
	while (*str && *str != c)
		*str_new++ = *str++;
	return (check);
}
