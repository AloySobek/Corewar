/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_scheduler_obj.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 18:27:20 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/12 14:03:30 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_SCHEDULER_OBJECT_H
# define CW_SCHEDULER_OBJECT_H

# include "cw_obj_container.h"

# define SC_PLAYERS_AMOUNT_I	p_scheduler_instance->players_amount
# define SC_PROCESSES_AMOUNT_I	p_scheduler_instance->processes_amount
# define SC_PLAYERS_LIST_I		p_scheduler_instance->p_players_list
# define SC_PROCESSES_LIST_I	p_scheduler_instance->p_processes_list
# define SC_TREE_TIME_I(X)		p_scheduler_instance->pa_avl_tree_timeline[X]
# define SC_LIST_TIME_I(X)		p_scheduler_instance->pa_list_timeline[X]

# define SC_END_GAME			-777
# define SC_MAX_CYCLE_SUPPORT	50000

# define SC_OBJ_NAME			"SCHEDULER"
# define SC_OBJ_ERROR			"Memory for SCHEDULER has not been allocated"
# define SC_TREE_ERROR			"Memory for SCHEDULER->AVL_TREE has not benn allocated"

typedef struct		s_scheduler
{
	t_mark			nearest_cycle;

	t_flag			avl_tree_timeline_on;
	t_flag			list_timeline_on;

	t_counter		players_amount;
	t_counter		processes_amount;

	t_player		*p_players_list;
	t_process		*p_processes_list;

	t_queue			**pa_timeline;

	t_method		(*cw_constructor)			(struct s_scheduler **);
	t_method		(*cw_insert_process)		(struct s_scheduler *, t_process *, int);
	t_method		(*cw_delete_process)		(struct s_scheduler *, t_process **, int);
	t_method		(*cw_insert_player)			(struct s_scheduler *, t_player *);
	t_method		(*cw_timeline_init)			(struct s_scheduler *, t_corewar *);
	t_method		(*cw_execution_processes)	(struct s_scheduler *, t_corewar *);
	t_method		(*cw_deadline)				(struct s_scheduler *, t_corewar *);
	t_method		(*cw_destructor)			(struct s_scheduler **);
}					t_scheduler;

void				cw_create_instance_scheduler	(t_scheduler **pp_scheduler_obj);
void				cw_scheduler_insertion_linker	(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref);
void				cw_scheduler_functions_linker	(t_scheduler *p_scheduler_instance, t_corewar *p_game_ref);

#endif
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
