/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:40:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/06 17:15:37 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_main_checking(t_corewar *p_game_instance)
{
	;
}

static void		cw_start_game(t_corewar *p_game_instance)
{
	// while (p_game_instance->p_scheduler->p_waiting_queue->p_current_carriage && ++p_game_instance->p_arena_obj->cycle_amount)
	// {
	// 	if (p_game_instance->p_arena_obj->cw_time_to_check(p_game_instance->p_arena_obj, p_game_instance->last_check_cycle))
	// 	{
	// 		p_game_instance->p_arena_obj->check_amount += 1;
	// 		p_game_instance->last_check_cycle = p_game_instance->p_arena_obj->cycle_amount;
	// 		while (p_game_instance->p_scheduler->p_waiting_queue->p_current_carriage && p_game_instance->p_scheduler->p_waiting_queue->p_current_carriage->nearest_cycle == p_game_instance->p_arena_obj->cycle_amount)
	// 		{
	// 			p_game_instance->p_scheduler->p_waiting_queue->cw_dequeue(p_game_instance->p_scheduler->p_waiting_queue, &p_game_instance->p_carriage_obj);
	// 			p_game_instance->p_carriage_obj->cw_set_command_time(p_game_instance->p_carriage_obj, p_game_instance->p_arena_obj);
	// 			p_game_instance->p_carriage_obj->cw_exec_command(p_game_instance->p_carriage_obj, p_game_instance);
	// 			if (p_game_instance->p_arena_obj->cycle_to_die <= (p_game_instance->p_arena_obj->cycle_amount - p_game_instance->p_carriage_obj->last_speak_cycle) || p_game_instance->p_arena_obj->cycle_to_die <= 0)
	// 				p_game_instance->p_carriage_obj->cw_destructor(&p_game_instance->p_carriage_obj);
	// 			else
	// 				p_game_instance->p_scheduler->p_waiting_queue->cw_enqueue(p_game_instance->p_scheduler->p_waiting_queue, p_game_instance->p_carriage_obj);
	// 		}
	// 		if (p_game_instance->p_arena_obj->live_amount >= NBR_LIVE || p_game_instance->p_arena_obj->check_amount >= MAX_CHECKS)
	// 		{
	// 			p_game_instance->p_arena_obj->cycle_to_die -= CYCLE_DELTA;
	// 			p_game_instance->p_arena_obj->check_amount = 0;
	// 		}
	// 		p_game_instance->p_arena_obj->live_amount = 0;
	// 	}
	// 	else
	// 		while (p_game_instance->p_scheduler->p_waiting_queue->p_current_carriage->nearest_cycle == p_game_instance->p_arena_obj->cycle_amount)
	// 		{
	// 			p_game_instance->p_scheduler->p_waiting_queue->cw_dequeue(p_game_instance->p_scheduler->p_waiting_queue, &p_game_instance->p_carriage_obj);
	// 			p_game_instance->p_carriage_obj->cw_set_command_time(p_game_instance->p_carriage_obj, p_game_instance->p_arena_obj);
	// 			p_game_instance->p_carriage_obj->cw_exec_command(p_game_instance->p_carriage_obj, p_game_instance);
	// 			p_game_instance->p_scheduler->p_waiting_queue->cw_enqueue(p_game_instance->p_scheduler->p_waiting_queue, p_game_instance->p_carriage_obj);
	// 		}
	// 	if (p_game_instance->p_arena_obj->cycle_amount == p_game_instance->cycle_dump && p_game_instance->p_scheduler->p_waiting_queue->p_current_carriage)
	// 	{
	// 		p_game_instance->p_scheduler->p_waiting_queue->cw_print_content(p_game_instance->p_scheduler->p_waiting_queue);
	// 		p_game_instance->p_arena_obj->cw_print_field(p_game_instance->p_arena_obj);
	// 	}
	// }
	;
}

static void		cw_start_graphic_game(t_corewar *p_game_instance)
{
	;
}

extern void		cw_game_process_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_start_graphic_game	= cw_start_graphic_game;
	p_game_instance->cw_main_checking		= cw_main_checking;
	p_game_instance->cw_start_game			= cw_start_game;
}
