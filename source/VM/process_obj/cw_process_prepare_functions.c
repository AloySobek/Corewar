/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_prepare_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:18:37 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 20:07:03 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_exec_command(t_process *p_process_instance,
							t_corewar *p_game_instance)
{
	if (!PR_CURRENT_COMMAND_I)
	{
		p_process_instance->cw_move_to(p_process_instance, 1);
		PR_NEAREST_CYCLE_I = p_game_instance->p_arena_obj->cycle + 1;
	}
	else if (PR_NEAREST_CYCLE_I == p_game_instance->p_arena_obj->cycle)
	{
		PR_CURRENT_COMMAND_I->cw_callback(p_game_instance);
		PR_CURRENT_COMMAND_I = NULL;
		PR_WAITING_TIME_I = 0;
		PR_NEAREST_CYCLE_I = p_game_instance->p_arena_obj->cycle + 1;
	}
}

static void	cw_set_command_time(t_process *p_process_instance,
									t_arena *p_arena_obj)
{
	if (PR_CURRENT_COMMAND_I || AR_FIELD_O[PR_CURRENT_LOCATION_I] < CO_LIVE
	|| AR_FIELD_O[PR_CURRENT_LOCATION_I] > CO_AFF)
		return ;
	PR_CURRENT_COMMAND_I =
		PR_COMMAND_CONTAINER_I[AR_FIELD_O[PR_CURRENT_LOCATION_I]];
	PR_NEAREST_CYCLE_I = AR_CYCLE_O + PR_CURRENT_COMMAND_I->waiting_time - 1;
	p_process_instance->cw_save_pos(p_process_instance, PR_MAIN_SAVE);
	PR_ERROR_OCCURED_I = CW_FALSE;
	PR_OFFSET_I = 0;
}

static void	cw_set_owner(t_process *p_process_instance,
							t_player *p_player_list, int players_amount)
{
	t_iter	iter;

	iter = CW_ITERATOR;
	while (++iter < players_amount)
	{
		if (p_player_list->id == PR_ID_I)
			PR_OWNER_I = p_player_list;
		p_player_list = p_player_list->p_next;
	}
}

extern void	cw_process_prepare_functions_linker(t_process *p_process_instance)
{
	p_process_instance->cw_set_owner = cw_set_owner;
	p_process_instance->cw_set_command_time = cw_set_command_time;
	p_process_instance->cw_exec_command = cw_exec_command;
}
