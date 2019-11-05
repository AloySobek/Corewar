/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:46:34 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/05 19:04:21 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_insert(t_scheduler *p_scheduler_instance)
{
	;
}

static void		cw_kick_players(t_scheduler *p_scheduler_instance)
{
	;
}

static void		cw_queues_init(t_scheduler *p_scheduler_instance)
{
	t_counter	iter;
	t_queue		*p_queue;

	iter = CW_ITERATOR;
	while (++iter < SC_MAX_CYCLE_SUPPORT)
	{
		cw_create_instance_queue(&p_queue);
		p_scheduler_instance->pa_timeline[iter] = p_queue;
	}
}

extern void	cw_scheduler_functions_linker(t_scheduler *p_scheduler_instance)
{
	p_scheduler_instance->cw_queues_init = cw_queues_init;
	p_scheduler_instance->cw_kick_players = cw_kick_players;
	p_scheduler_instance->cw_queues_init = cw_queues_init;
}