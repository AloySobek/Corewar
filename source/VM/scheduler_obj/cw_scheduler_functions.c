/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 14:46:34 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/04 17:05:20 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_relax_waiting_queue(t_scheduler *p_scheduler_instance, t_corewar *p_game_obj)
{
	t_carriage	*tmp;

	while (p_scheduler_instance->p_waiting_queue->p_current_carriage->nearest_cycle == p_game_obj->p_arena_obj->cycle_amount)
	{
			;
	}
}

static void		cw_distribute_quantums(t_scheduler *p_scheduler_instance, t_corewar *p_game_obj)
{
	t_carriage	*tmp;

	while (p_scheduler_instance->p_distribution_stack->p_current_carriage)
	{
		p_scheduler_instance->p_distribution_stack->p_current_carriage->cw_set_command_time(p_scheduler_instance->p_distribution_stack->p_current_carriage, p_game_obj->p_arena_obj);
		p_scheduler_instance->p_distribution_stack->cw_pop(p_scheduler_instance->p_distribution_stack, &tmp, NULL);
		if (p_scheduler_instance->p_distribution_stack->p_current_carriage->p_current_command && p_scheduler_instance->p_distribution_stack->p_current_carriage->nearest_cycle != p_game_obj->p_arena_obj->cycle_amount)
			p_scheduler_instance->p_waiting_queue->cw_enqueue(p_scheduler_instance->p_waiting_queue, tmp);
		else
			p_scheduler_instance->p_execution_queue->cw_enqueue(p_scheduler_instance->p_execution_queue, tmp);
	}
}

static void		cw_kick_players(t_scheduler *p_scheduler_instance)
{
	while (p_scheduler_instance->p_players_room->p_current_player)
		p_scheduler_instance->p_players_room->cw_pop(p_scheduler_instance->p_players_room, NULL, NULL);
}

static void		cw_kill_processes(t_scheduler *p_scheduler_instance)
{
	while (p_scheduler_instance->p_distribution_stack->p_current_carriage)
		p_scheduler_instance->p_distribution_stack->cw_pop(p_scheduler_instance->p_distribution_stack, NULL, NULL);
}

static void		cw_queues_init(t_scheduler *p_scheduler_instance)
{
	t_queue		*p_queue;

	cw_create_instance_queue(&p_queue);
	p_scheduler_instance->p_waiting_queue = p_queue;
	cw_create_instance_queue(&p_queue);
	p_scheduler_instance->p_execution_queue = p_queue;
}

static void		cw_stacks_init(t_scheduler *p_scheduler_instance)
{
	t_stack		*p_stack;

	cw_create_instance_stack(&p_stack);
	p_scheduler_instance->p_distribution_stack = p_stack;
	cw_create_instance_stack(&p_stack);
	p_scheduler_instance->p_players_room = p_stack;
}

extern void	cw_scheduler_functions_linker(t_scheduler *p_scheduler_instance)
{
	p_scheduler_instance->cw_stacks_init = cw_stacks_init;
	p_scheduler_instance->cw_queues_init = cw_queues_init;
	p_scheduler_instance->cw_kick_players = cw_kick_players;
	p_scheduler_instance->cw_kill_processes = cw_kill_processes;
	p_scheduler_instance->cw_distribute_quantums = cw_distribute_quantums;
	p_scheduler_instance->cw_relax_waiting_queue = cw_relax_waiting_queue;
}