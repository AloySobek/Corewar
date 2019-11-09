/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 19:54:49 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/17 10:44:57 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	res_str[12];
	char	*check;
	int		count;
	int		minus;
	char	*result;

	check = ft_strnew(ft_nbrlen(n));
	count = 0;
	if (!(result = check))
		return (result);
	if (n < 0 || !(minus = 1))
	{
		minus = -1;
		*check++ = '-';
	}
	if (n == 0)
		*check++ = '0';
	while (n != 0)
	{
		res_str[count++] = ((n % 10) * minus) + '0';
		n /= 10;
	}
	while (--count >= 0)
		*check++ = res_str[count];
	return (result);
}
