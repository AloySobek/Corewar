/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:24:27 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/12 14:16:42 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_deadline(t_scheduler *p_scheduler_instance,
								t_corewar *p_game_obj)
{
	t_iterator	check_point;
	t_process	*iter;

	iter = p_scheduler_instance->p_processes_list;
	check_point = p_scheduler_instance->processes_amount;
	p_game_obj->p_arena_obj->check_amount += 1;
	p_game_obj->last_check_cycle = p_game_obj->p_arena_obj->cycle;
	while (check_point-- && iter)
	{
		iter ? iter->p_owner->live_amount = 0 : 0;
		if (p_game_obj->AR_CYCLE_TO_DIE_O <= (p_game_obj->AR_CYCLE_O -
		iter->last_speak_cycle) || p_game_obj->AR_CYCLE_TO_DIE_O <= 0)
			p_scheduler_instance->cw_delete_process(p_scheduler_instance,
				&iter, p_game_obj->AR_CYCLE_O);
		else
			iter ? iter = iter->p_next : CW_FALSE;
	}
	if (p_game_obj->AR_LIVE_AMOUNT_O >= NBR_LIVE ||
	p_game_obj->AR_CHECK_AMOUNT_O >= MAX_CHECKS)
	{
		p_game_obj->AR_CYCLE_TO_DIE_O -= CYCLE_DELTA;
		p_game_obj->AR_CHECK_AMOUNT_O = 0;
	}
	p_game_obj->AR_LIVE_AMOUNT_O = 0;
}

static void		cw_ordinary_execution_processes(
					t_scheduler *p_scheduler_instance, t_corewar *p_game_obj)
{
	t_process	*iter;
	t_iterator	i;
	t_mark		check_point;

	i = CW_ITERATOR;
	iter = p_scheduler_instance->p_processes_list;
	check_point = p_scheduler_instance->processes_amount;
	while (++i < check_point)
	{
		p_game_obj->p_working_process = iter;
		iter->cw_set_command_time(iter, p_game_obj);
		iter->cw_exec_command(iter, p_game_obj);
		iter = iter->p_next;
	}
}

static void		cw_timeline_execution_processes(
					t_scheduler *p_scheduler_instance, t_corewar *p_game_obj)
{
	;
}

static void		cw_timeline_init(t_scheduler *p_scheduler_instance,
										t_corewar *p_game_obj)
{
	t_counter	iter;
	t_queue		*p_queue;

	iter = CW_ITERATOR;
	if (!(p_scheduler_instance->pa_timeline =
	(t_queue **)malloc(sizeof(t_queue *) * SC_MAX_CYCLE_SUPPORT)))
		cw_error_catcher(SC_OBJ_NAME, SC_TREE_ERROR, __FILE__, __LINE__);
	while (++iter < SC_MAX_CYCLE_SUPPORT)
	{
		cw_create_instance_queue(&p_queue);
		p_queue->game_ref = p_game_obj;
		p_scheduler_instance->pa_timeline[iter] = p_queue;
	}
}

extern void		cw_scheduler_functions_linker(t_scheduler *p_scheduler_instance,
												t_corewar *p_game_obj)
{
	p_scheduler_instance->cw_timeline_init = cw_timeline_init;
	p_scheduler_instance->cw_deadline = cw_deadline;
	if (p_game_obj)
		if (GA_TREE_TIME_O || GA_LIST_TIME_O)
			p_scheduler_instance->cw_execution_processes =
				cw_timeline_execution_processes;
		else
			p_scheduler_instance->cw_execution_processes =
				cw_ordinary_execution_processes;
	else
		p_scheduler_instance->cw_execution_processes =
			cw_ordinary_execution_processes;
}
