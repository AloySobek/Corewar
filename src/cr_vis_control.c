/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:50:13 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/21 19:18:10 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vis.h"
#include "../inc/asm.h"
#include "../inc/corewar.h"
#include "../inc/op.h"

int		cr_vis_timer(t_vis	*vis)
{
	long int check;

	if (!vis->time)
		vis->time = clock();
	if (time < 0)
		return (1);
	check = clock();
	mvprintw(40, 210, "time: %d | check: %d", vis->time, check);
	if ((check - vis->time) >= (CLOCKS_PER_SEC / 100))
	{
		vis->step = vis->step ? 0 : 1;
		vis->time = check;
	}
	return (0);
}

int		cr_vis_keys(t_vis *vis)
{
	int key;

	key = getch();
	if (key == KEY_F(1))
		vis->exit = 1;
	return (0);
}