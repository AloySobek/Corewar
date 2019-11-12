/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:24:27 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/11 22:06:01 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "corewar.h"

static void		cw_deadline(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref)
{
	t_process	*iter;
	t_iterator	i;
	t_mark		check_point;

	i = CW_ITERATOR;
	iter = p_scheduler_instance->p_processes_list;
	check_point = p_scheduler_instance->processes_amount;
	p_game_ref->p_arena_obj->check_amount += 1;
	ft_printf("%d\n", p_game_ref->p_arena_obj->cycle);
	p_game_ref->last_check_cycle = p_game_ref->p_arena_obj->cycle;
	while (++i < check_point && iter)
	{
		iter->p_owner->live_amount = 0;
		if (p_game_ref->p_arena_obj->cycle_to_die <= (p_game_ref->p_arena_obj->cycle - iter->last_speak_cycle) || p_game_ref->p_arena_obj->cycle_to_die <= 0)
			p_scheduler_instance->cw_delete_process(p_scheduler_instance, &iter, p_game_ref->p_arena_obj->cycle);
		else
			iter ? iter = iter->p_next : 0;
	}
	if (p_game_ref->p_arena_obj->live_amount >= NBR_LIVE || p_game_ref->p_arena_obj->check_amount >= MAX_CHECKS)
	{
		p_game_ref->p_arena_obj->cycle_to_die -= CYCLE_DELTA;
		p_game_ref->p_arena_obj->check_amount = 0;
	}
	p_game_ref->p_arena_obj->live_amount = 0;
}

static void		cw_executon_processes(t_scheduler *p_scheduler_instance)
{
	;
}

static void		cw_ordinary_execution_processes(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref)
{
	t_process	*iter;
	t_iterator	i;
	t_mark		check_point;

	i = CW_ITERATOR;
	iter = p_scheduler_instance->p_processes_list;
	check_point = p_scheduler_instance->processes_amount;
	//if (p_game_ref->p_arena_obj->cycle == 24402)
	//{
		ft_printf("%d\n", check_point);
		for (int i = 0; i < p_scheduler_instance->processes_amount; ++i)
		{
			ft_printf("%d\n", p_scheduler_instance->p_processes_list->id);
			p_scheduler_instance->p_processes_list = p_scheduler_instance->p_processes_list->p_next;
		}
	//}
	while (++i < check_point)
	{
		p_game_ref->p_working_process = iter;
		iter->cw_set_command_time(iter, p_game_ref);
		iter->cw_exec_command(iter, p_game_ref);
		iter = iter->p_next;
	}
}

static void		cw_timeline_execution_processes(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref)
{
	;
}

static void		cw_data_struct_init(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref)
{
	t_counter	iter;
	t_queue		*p_queue;

	iter = CW_ITERATOR;
	if (p_scheduler_instance->avl_tree_timeline_on || p_scheduler_instance->list_timeline_on)
	{
		if (p_scheduler_instance->avl_tree_timeline_on)
		{
			if (!(p_scheduler_instance->pa_avl_tree_timeline = (t_queue **)malloc(sizeof(t_queue *) * SC_MAX_CYCLE_SUPPORT)))
				cw_error_catcher(SC_OBJ_NAME, SC_TREE_ERROR, __FILE__, __LINE__);
		}
		else
			if (!(p_scheduler_instance->pa_list_timeline = (t_queue **)malloc(sizeof(t_queue *) * SC_MAX_CYCLE_SUPPORT)))
				cw_error_catcher(SC_OBJ_NAME, SC_TREE_ERROR, __FILE__, __LINE__);
		while (++iter < SC_MAX_CYCLE_SUPPORT)
		{
			cw_create_instance_queue(&p_queue);
			p_queue->game_ref = p_game_ref;
			p_scheduler_instance->avl_tree_timeline_on
			? (p_scheduler_instance->pa_avl_tree_timeline[iter] = p_queue)
			: (p_scheduler_instance->pa_list_timeline[iter] = p_queue);
		}
	}
	else
		p_scheduler_instance->p_processes_list = NULL;
}

extern void		cw_scheduler_functions_linker(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref)
{
	p_scheduler_instance->cw_data_struct_init = cw_data_struct_init;
	p_scheduler_instance->cw_deadline = cw_deadline;
	if (p_game_ref)
		if (p_game_ref->timeline_avl_tree_mode || p_game_ref->timeline_list_mode)
			p_scheduler_instance->cw_execution_processes = cw_timeline_execution_processes;
		else
			p_scheduler_instance->cw_execution_processes = cw_ordinary_execution_processes;
	else
		p_scheduler_instance->cw_execution_processes = cw_ordinary_execution_processes;
}

// int deleted_count;

	// while (p_game_instance->carriages_amount > 0 && ++p_game_instance->p_arena_obj->cycle)
	// {
	// 	p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle]->cw_exec_processes(p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle], p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle]->p_root);
	// 	//p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle]->cw_print_content(p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle], p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle]->p_root, 0);
	// 	if (p_game_instance->p_arena_obj->cw_time_to_check(p_game_instance->p_arena_obj, p_game_instance->last_check_cycle))
	// 	{
	// 		p_game_instance->p_arena_obj->check_amount += 1;
	// 		p_game_instance->last_check_cycle = p_game_instance->p_arena_obj->cycle;
	// 		deleted_count = 0;
	// 		for (int i = 0; i < p_game_instance->p_scheduler->processes_amount; ++i)
	// 		{
	// 			p_game_instance->p_scheduler->p_carriage_obj ? p_game_instance->p_scheduler->p_carriage_obj->p_owner->live_amount = 0 : CW_FALSE;
	// 			if (p_game_instance->p_scheduler->p_carriage_obj && (p_game_instance->p_arena_obj->cycle_to_die <= (p_game_instance->p_arena_obj->cycle - p_game_instance->p_scheduler->p_carriage_obj->last_speak_cycle) || p_game_instance->p_arena_obj->cycle_to_die <= 0))
	// 			{
	// 				t_process      *p_tmp_carrriage;

	// 				p_tmp_carrriage = p_game_instance->p_scheduler->p_carriage_obj;
	// 				p_game_instance->p_scheduler->p_carriage_obj->kill = CW_TRUE;
	// 				if (p_game_instance->p_scheduler->p_carriage_obj)
	// 				{
	// 					if (p_game_instance->p_scheduler->p_carriage_obj->p_next == p_game_instance->p_scheduler->p_carriage_obj)
	// 						p_game_instance->p_scheduler->p_carriage_obj = NULL;
	// 					else
	// 					{
	// 						p_game_instance->p_scheduler->p_carriage_obj->p_prev->p_next = p_game_instance->p_scheduler->p_carriage_obj->p_next;
	// 						p_game_instance->p_scheduler->p_carriage_obj->p_next->p_prev = p_game_instance->p_scheduler->p_carriage_obj->p_prev;
	// 						p_game_instance->p_scheduler->p_carriage_obj = p_game_instance->p_scheduler->p_carriage_obj->p_next;
	// 					}
	// 				}
    //     			deleted_count += 1;
	// 			}
	// 			else
	// 				p_game_instance->p_scheduler->p_carriage_obj ? p_game_instance->p_scheduler->p_carriage_obj = p_game_instance->p_scheduler->p_carriage_obj->p_next : CW_FALSE;
	// 		}
	// 		if (p_game_instance->p_arena_obj->live_amount >= NBR_LIVE || p_game_instance->p_arena_obj->check_amount >= MAX_CHECKS)
	// 		{
	// 			p_game_instance->p_arena_obj->cycle_to_die -= CYCLE_DELTA;
	// 			p_game_instance->p_arena_obj->check_amount = 0;
	// 		}
	// 		p_game_instance->carriages_amount -= deleted_count;
	// 		p_game_instance->p_arena_obj->live_amount = 0;
	// 	}
	// 	if (p_game_instance->cycle_dump == p_game_instance->p_arena_obj->cycle && p_game_instance->carriages_amount > 0)
	// 		p_game_instance->p_arena_obj->cw_print_field(p_game_instance->p_arena_obj);
	// }