/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 13:27:40 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/18 16:54:14 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	int		nbr[10];
	int		count;
	int		minus;

	minus = 1;
	count = 0;
	if (n < 0)
	{
		ft_putchar('-');
		minus = -1;
	}
	while (n != 0)
	{
		nbr[count] = (n % 10) * minus;
		n /= 10;
		count++;
	}
	if (count > 0)
		count--;
	while (count >= 0)
	{
		ft_putchar(nbr[count] + '0');
		count--;
	}
}
