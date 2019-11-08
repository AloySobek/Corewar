/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:40:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/08 19:45:39 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_main_checking(t_corewar *p_game_instance)
{
	;
}

static void		cw_start_game(t_corewar *p_game_instance)
{
	int deleted_count;

	while (p_game_instance->carriages_amount > 0 && ++p_game_instance->p_arena_obj->cycle)
	{
		p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle]->cw_exec_processes(p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle], p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle]->p_root);
		//p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle]->cw_print_content(p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle], p_game_instance->p_scheduler->pa_timeline[p_game_instance->p_arena_obj->cycle]->p_root, 0);
		if (p_game_instance->p_arena_obj->cw_time_to_check(p_game_instance->p_arena_obj, p_game_instance->last_check_cycle))
		{
			p_game_instance->p_arena_obj->check_amount += 1;
			p_game_instance->last_check_cycle = p_game_instance->p_arena_obj->cycle;
			deleted_count = 0;
			for (int i = 0; i < p_game_instance->p_scheduler->processes_amount; ++i)
			{
				p_game_instance->p_scheduler->p_process_obj ? p_game_instance->p_scheduler->p_process_obj->p_owner->live_amount = 0 : CW_FALSE;
				if (p_game_instance->p_scheduler->p_process_obj && (p_game_instance->p_arena_obj->cycle_to_die <= (p_game_instance->p_arena_obj->cycle - p_game_instance->p_scheduler->p_process_obj->last_speak_cycle) || p_game_instance->p_arena_obj->cycle_to_die <= 0))
				{
					t_process      *p_tmp_carrriage;

					p_tmp_carrriage = p_game_instance->p_scheduler->p_process_obj;
					p_game_instance->p_scheduler->p_process_obj->kill = CW_TRUE;
					if (p_game_instance->p_scheduler->p_process_obj)
					{
						if (p_game_instance->p_scheduler->p_process_obj->p_next == p_game_instance->p_scheduler->p_process_obj)
							p_game_instance->p_scheduler->p_process_obj = NULL;
						else
						{
							p_game_instance->p_scheduler->p_process_obj->p_prev->p_next = p_game_instance->p_scheduler->p_process_obj->p_next;
							p_game_instance->p_scheduler->p_process_obj->p_next->p_prev = p_game_instance->p_scheduler->p_process_obj->p_prev;
							p_game_instance->p_scheduler->p_process_obj = p_game_instance->p_scheduler->p_process_obj->p_next;
						}
					}
        			deleted_count += 1;
				}
				else
					p_game_instance->p_scheduler->p_process_obj ? p_game_instance->p_scheduler->p_process_obj = p_game_instance->p_scheduler->p_process_obj->p_next : CW_FALSE;
			}
			if (p_game_instance->p_arena_obj->live_amount >= NBR_LIVE || p_game_instance->p_arena_obj->check_amount >= MAX_CHECKS)
			{
				p_game_instance->p_arena_obj->cycle_to_die -= CYCLE_DELTA;
				p_game_instance->p_arena_obj->check_amount = 0;
			}
			p_game_instance->carriages_amount -= deleted_count;
			p_game_instance->p_arena_obj->live_amount = 0;
		}
		if (p_game_instance->cycle_dump == p_game_instance->p_arena_obj->cycle && p_game_instance->carriages_amount > 0)
			p_game_instance->p_arena_obj->cw_print_field(p_game_instance->p_arena_obj);
	}
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
