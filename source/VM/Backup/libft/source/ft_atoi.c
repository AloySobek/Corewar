/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:56:15 by vrichese          #+#    #+#             */
/*   Updated: 2019/06/19 17:20:25 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int							ft_atoi(const char *str)
{
	int						minus;
	int						res;
	unsigned long long int	check;

	minus = 1;
	res = 0;
	check = 0;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			minus = -1;
	while (*str >= 48 && *str <= 57)
	{
		res = (res * 10) + (*str - '0');
		check = (check * 10) + (*str++ - '0');
		if (check > 9223372036854775807)
		{
			if (minus == 1)
				return (-1);
			if (minus == -1)
				return (0);
		}
	}
	return (res * minus);
}
