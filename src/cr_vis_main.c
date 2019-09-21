/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 12:31:47 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/21 19:04:39 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vis.h"
#include "asm.h"
#include "corewar.h"
#include "op.h"

int		cr_vis_main(corewar_t *cr)
{
	t_vis	*vis;
	int		num[4 * 1024];
	int		i = -1;

	vis = cr_vis_initvis();
	ft_bzero(num, sizeof(int) * 4 * 1024);
	while (++i < 250)
		num[i] = i;
	cr_vis_initterm();
	cr_vis_initcolour();
	cr_vis_drawborder();
	while (!vis->exit)
	{
		cr_vis_keys(vis);
		cr_vis_timer(vis);
		cr_vis_printmap(num, 4 * 1024, vis);
		refresh();
	}
	cr = NULL;	
	endwin();
	return (0);
}

int		main()
{
	corewar_t *cr;

	cr = (corewar_t *)malloc(sizeof(corewar_t));
	ft_bzero(cr, sizeof(corewar_t));
	cr_vis_main(cr);
	return (0);
}