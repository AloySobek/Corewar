/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:31:47 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/23 18:40:33 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		cr_vis_cleanup(corewar_t *cr)
{
	free(cr->vis);
	cr->vis = NULL;
	endwin();
	return (0);
}

int		cr_vis_main(corewar_t *cr)
{
	mvprintw(6, 230, "%d", (mvinch(3, 10) & A_COLOR));
	cr_vis_keys(cr->vis);
	cr_vis_timer(cr->vis);
	if ((cr->vis->step || cr->vis->flow) && cr->vis->tick)
		mvprintw(21, 210, "hello there ~ <3");
	else if (cr->vis->tick)
		mvprintw(21, 210, "fuck you                   ");
	cr->vis->step = !cr->vis->tick ? cr->vis->step : 0;
	cr->vis->tick = 0;
	refresh();
	return (0);
}