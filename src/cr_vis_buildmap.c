/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_buildmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:52:16 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/21 19:18:20 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vis.h"
#include "../inc/asm.h"
#include "../inc/corewar.h"
#include "../inc/op.h"

void		cr_vis_putx(int num, int y, int x, int rev)
{
	char	ret[3];
	char	*power = "0123456789abcdef";

	ft_bzero(ret, 3);
	ret[1] = power[num % 16];
	num = num / 16;
	ret[0] = power[num % 16];
	cr_vis_printattr(y, x, ret, 2, rev);
}

int		cr_vis_printattr(int y, int x, char *str, int colour, int reverse)
{
	if (colour)
		attron(COLOR_PAIR(colour));
	if (reverse)	
		attron(A_REVERSE);
	mvaddstr(y, x, str);
	if (colour)
		attroff(COLOR_PAIR(colour));
	if (reverse)	
		attroff(A_REVERSE);
	return (0);
}

int		cr_vis_drawborder(void)
{
	int x;
	int y;

	y = -1;
	while (++y < 80)
	{
		x = -1;
		while (++x < 260)
		{
			if (x == 0 || x == 1 || y == 0 || x == V_W - 1 ||
			y == V_H - 1 || x == V_W - 2 || x == V_SEP ||
			x == V_SEP - 1)
				mvaddstr(y, x, V_BSYM);
		}	
	}
	return (0);
}

int		cr_vis_printmap(int *f, int f_len, t_vis *vis)
{
	int		i;
	int		x;
	int		y;

	x = 5;
	y = 2;
	i = 0;
	while (i < f_len)
	{
		cr_vis_putx(f[i], y, x, vis->step);
		mvprintw(30, 240, "vis->step: %d", vis->step);
		if (x >= V_SEP - 6)
		{
			x = 5;
			y += 1;
		}
		else   
			x += 3;
		i += 1;
	}
	return (0);
}