/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:40:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/11 22:05:36 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_start_execution(t_corewar *p_game_instance)
{
	while (p_game_instance->p_scheduler->processes_amount && ++p_game_instance->p_arena_obj->cycle)
	{
		if (p_game_instance->p_scheduler->nearest_cycle == p_game_instance->p_arena_obj->cycle)
			p_game_instance->p_scheduler->cw_execution_processes(p_game_instance->p_scheduler, p_game_instance);
		if (p_game_instance->p_arena_obj->cw_time_to_check(p_game_instance->p_arena_obj, p_game_instance->last_check_cycle))
			p_game_instance->p_scheduler->cw_deadline(p_game_instance->p_scheduler, p_game_instance);
		if (p_game_instance->dump_cycle == p_game_instance->p_arena_obj->cycle && p_game_instance->p_scheduler->processes_amount)
			p_game_instance->p_arena_obj->cw_print_field(p_game_instance->p_arena_obj);
	}
}

extern void		cw_game_process_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_start_execution = cw_start_execution;
}
