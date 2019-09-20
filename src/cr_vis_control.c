/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:31:47 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/20 18:32:30 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vis.h"
#include "asm.h"
#include "corewar.h"
#include "op.h"

void		cr_vis_putx(int num, int y, int x)
{
	char	ret[3];
	char	*power = "0123456789abcdef";

	ft_bzero(ret, 3);
	ret[1] = power[num % 16];
	num = num / 16;
	ret[0] = power[num % 16];
	mvprintw(y, x, "%s", ret);
}

int		cr_vis_initterm(void)
{
	system("printf '\033[8;68;260t'");
	setlocale(LC_ALL, "");
	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	// attron(A_BOLD);
	refresh();
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

int		cr_vis_printhex(int *f, int f_len)
{
	int		i;
	int		x;
	int		y;

	x = 5;
	y = 2;
	i = 0;
	while (i < f_len)
	{
		cr_vis_putx(f[i], y, x);
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

int		cr_vis_control(corewar_t *cr)
{
	int num[4 * 1024];
	int i = -1;

	ft_bzero(num, sizeof(int) * 4 * 1024);
	while (++i < 250)
		num[i] = i;
	cr_vis_initterm();
	cr_vis_drawborder();
	cr_vis_printhex(num, 4 * 1024);
	refresh();
	while (getch() != KEY_F(1))
		;
	cr = NULL;	
	endwin();
	return (0);
}

int		main()
{
	corewar_t *cr;

	cr = (corewar_t *)malloc(sizeof(corewar_t));
	ft_bzero(cr, sizeof(corewar_t));
	cr_vis_control(cr);
	return (0);
}