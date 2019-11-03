/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:40:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/03 20:11:26 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_main_checking(t_corewar *p_game_instance)
{
	// t_carriage	*tmp;
	// int			deleted_count;
	// int			iter;

	// iter = CW_ITERATOR;
	// deleted_count = 0;
	// p_game_instance->p_arena_obj->check_amount += 1;
	// p_game_instance->last_check_cycle = p_game_instance->p_arena_obj->cycle_amount;
	// while (++iter < p_game_instance->carriages_amount && p_game_instance->p_carriage_obj)
	// {
	// 	p_game_instance->p_carriage_obj ? p_game_instance->p_carriage_obj->p_owner->live_amount = 0 : CW_FALSE;
	// 	if (p_game_instance->p_arena_obj->cycle_to_die <= (p_game_instance->p_arena_obj->cycle_amount - p_game_instance->p_carriage_obj->last_speak_cycle) || p_game_instance->p_arena_obj->cycle_to_die <= 0)
	// 		p_game_instance->cw_delete_carriage(p_game_instance, &deleted_count);
	// 	else
	// 		p_game_instance->p_carriage_obj ? p_game_instance->p_carriage_obj = p_game_instance->p_carriage_obj->p_next : CW_FALSE;
	// }
	// if (p_game_instance->p_arena_obj->live_amount >= NBR_LIVE || p_game_instance->p_arena_obj->check_amount >= MAX_CHECKS)
	// {
	// 	p_game_instance->p_arena_obj->cycle_to_die -= CYCLE_DELTA;
	// 	p_game_instance->p_arena_obj->check_amount = 0;
	// }
	// p_game_instance->carriages_amount -= deleted_count;
	// p_game_instance->p_arena_obj->live_amount = 0;
	;
}

static void		cw_start_game(t_corewar *p_game_instance)
{
	int			iter;

	if (p_game_instance->visualizator)
		p_game_instance->cw_start_graphic_game(p_game_instance);
	else
		while (p_game_instance->p_scheduler->nearest_cycle != CW_END_GAME && ++p_game_instance->p_arena_obj->cycle_amount)
		{
			if (p_game_instance->p_scheduler->nearest_cycle == p_game_instance->p_arena_obj->cycle_amount)
			{
			;//	p_game_instance->p_scheduler->cw_distribute_quantums(p_game_instance->p_scheduler);
			}
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
