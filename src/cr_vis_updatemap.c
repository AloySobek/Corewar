/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis_updatemap.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:36:16 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/23 19:27:55 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// int		cr_vis_printcar(corewar_t *cr)
// {
// 	int			run;
// 	carriage_t	*car;

// 	car = cr->carriages;
// 	run = -1;
// 	while (++run < cr->carriages_amount)
// 	{
// 		cr_vis_putx(cr->arena->field[car->current_location], car->current_location, 0, 1);
// 		car = car->next;
// 	}
// }

int		cr_vis_printdiff(corewar_t *cr)
{
	int				i;
	unsigned char	*f_vis;
	unsigned char	*f_cr;

	i = -1;
	f_vis = cr->vis->field;
	f_cr = cr->arena->field;
	while (++i < MEM_SIZE)
	{
		if (f_vis[i] != f_cr[i])
		{
			cr_vis_putx(f_cr[i], i, 0, 1);
			f_vis[i] = f_cr[i];
		}
	}
	return (0);
}

int		cr_vis_updatemap(corewar_t *cr)
{
	cr_vis_printdiff(cr);
	// cr_vis_printcar(cr);
	refresh();
	return (0);
}