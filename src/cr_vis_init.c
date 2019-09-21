/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:44:47 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/21 19:01:25 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vis.h"
#include "../inc/asm.h"
#include "../inc/corewar.h"
#include "../inc/op.h"

t_vis	*cr_vis_initvis(void)
{
	t_vis *tmp;

	tmp = (t_vis *)malloc(sizeof(t_vis));
	ft_bzero(tmp, sizeof(t_vis));
	tmp->pause = 1;
	return (tmp);
}

int		cr_vis_initcolour(void)
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	return (0);
}

int		cr_vis_initterm(void)
{
	system("printf '\033[8;68;260t'");
	setlocale(LC_ALL, "");
	initscr();
	halfdelay(1);
	keypad(stdscr, TRUE);
	noecho();
	curs_set(0);
	start_color();
	refresh();
	return (0);
}