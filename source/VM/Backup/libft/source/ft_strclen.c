/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft-strclen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:26:51 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/19 12:46:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strclen(const char *str, char c)
{
	int count;

	count = 0;
	while (str[count] && str[count] != c)
		count++;
	return (count);
}
