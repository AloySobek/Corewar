/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:46:34 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 16:26:07 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_list_process(t_scheduler *p_scheduler_instance, t_process *p_adding_process)
{
	if (p_adding_process)
	{
		if (!p_scheduler_instance->p_process_obj)
		{
			p_adding_process->p_next = p_adding_process;
			p_adding_process->p_prev = p_adding_process;
			p_scheduler_instance->p_process_obj = p_adding_process;
		}
		else
		{
			p_adding_process->p_next = p_scheduler_instance->p_process_obj;
			p_adding_process->p_prev = p_scheduler_instance->p_process_obj->p_prev;
			p_scheduler_instance->p_process_obj->p_prev->p_next = p_adding_process;
			p_scheduler_instance->p_process_obj->p_prev = p_adding_process;
		}
		p_scheduler_instance->processes_amount += 1;
	}
}

static void		cw_insert_player(t_scheduler *p_scheduler_instance, t_player *p_adding_player)
{
	if (p_adding_player)
	{
		if (!p_scheduler_instance->p_player_obj)
		{
			p_adding_player->p_next = p_adding_player;
			p_adding_player->p_prev = p_adding_player;
			p_scheduler_instance->p_player_obj = p_adding_player;
		}
		else
		{
			p_adding_player->p_next = p_scheduler_instance->p_player_obj;
			p_adding_player->p_prev = p_scheduler_instance->p_player_obj->p_prev;
			p_scheduler_instance->p_player_obj->p_prev->p_next = p_adding_player;
			p_scheduler_instance->p_player_obj->p_prev = p_adding_player;
		}
		p_scheduler_instance->players_amount += 1;
	}
}

static void		cw_insert_process(t_scheduler *p_scheduler_instance, t_process *p_adding_process, int cycle)
{
	t_queue		*p_current_queue;

	p_current_queue = p_scheduler_instance->pa_timeline[cycle];
	p_current_queue->p_root = p_current_queue->cw_enqueue(p_current_queue, p_current_queue->p_root, p_adding_process);
}

static void		cw_kick_players(t_scheduler *p_scheduler_instance)
{
	t_counter	iter;
	t_player	*tmp;

	iter = CW_ITERATOR;
	while (++iter < p_scheduler_instance->players_amount)
	{
		tmp = p_scheduler_instance->p_player_obj->p_next;
		p_scheduler_instance->p_player_obj->cw_destructor(&p_scheduler_instance->p_player_obj);
		p_scheduler_instance->p_player_obj = tmp;
	}
}

static void		cw_queues_init(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref)
{
	t_counter	iter;
	t_queue		*p_queue;

	iter = CW_ITERATOR;
	while (++iter < SC_MAX_CYCLE_SUPPORT)
	{
		cw_create_instance_queue(&p_queue);
		p_queue->game_ref = p_game_ref;
		p_queue->pa_timeline = p_scheduler_instance->pa_timeline;
		p_scheduler_instance->pa_timeline[iter] = p_queue;
	}
}

extern void	cw_scheduler_functions_linker(t_scheduler *p_scheduler_instance)
{
	p_scheduler_instance->cw_queues_init = cw_queues_init;
	p_scheduler_instance->cw_kick_players = cw_kick_players;
	p_scheduler_instance->cw_queues_init = cw_queues_init;
	p_scheduler_instance->cw_insert_player = cw_insert_player;
	p_scheduler_instance->cw_insert_process = cw_insert_process;
	p_scheduler_instance->cw_list_process = cw_list_process;
}