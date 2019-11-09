/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 15:23:55 by vrichese          #+#    #+#             */
/*   Updated: 2019/04/16 15:34:04 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	nbr[10];
	int	count;
	int minus;

	minus = 1;
	count = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
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
		ft_putchar_fd((nbr[count] + '0'), fd);
		count--;
	}
}
