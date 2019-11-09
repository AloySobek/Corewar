/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 18:09:26 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/17 10:36:25 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *new_str;

	new_str = (char *)malloc(sizeof(char) * size + 1);
	if (new_str)
		ft_memset(new_str, '\0', size + 1);
	return (new_str);
}
