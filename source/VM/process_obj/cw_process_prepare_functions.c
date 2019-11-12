/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_prepare_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:18:37 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/11 22:03:45 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_exec_command(t_process *p_process_instance, t_corewar *p_game_obj)
{
	if (!p_process_instance->p_current_command)
	{
		p_process_instance->cw_move_to(p_process_instance, 1);
		p_process_instance->nearest_cycle = p_game_obj->p_arena_obj->cycle + 1;
	}
	else if (p_process_instance->nearest_cycle == p_game_obj->p_arena_obj->cycle)
	{
		p_process_instance->p_current_command->cw_callback(p_game_obj);
		p_process_instance->p_current_command = NULL;
		p_process_instance->waiting_time = 0;
		p_process_instance->nearest_cycle = p_game_obj->p_arena_obj->cycle + 1;
	}
}

void	cw_set_command_time(t_process *p_process_instance, t_corewar *p_game_obj)
{
	if (p_process_instance->p_current_command || p_game_obj->p_arena_obj->p_field[p_process_instance->current_location] < CO_LIVE || p_game_obj->p_arena_obj->p_field[p_process_instance->current_location] > CO_AFF)
		return ;
	p_process_instance->p_current_command = p_process_instance->pp_command_container[p_game_obj->p_arena_obj->p_field[p_process_instance->current_location]];
	p_process_instance->nearest_cycle = p_game_obj->p_arena_obj->cycle + p_process_instance->p_current_command->waiting_time - 1;
	p_process_instance->cw_save_pos(p_process_instance, PR_MAIN_SAVE);
	p_process_instance->error_ocurred = CW_FALSE;
	p_process_instance->offset = 0;
}

void	cw_set_owner(t_process *p_process_instance, t_scheduler *p_scheduler_obj)
{
	int	iter;

	iter = CW_ITERATOR;
	while (++iter < p_scheduler_obj->players_amount)
	{
		if (p_scheduler_obj->p_players_list->id > p_scheduler_obj->players_amount)
			cw_error_catcher(PL_OBJECT_NAME, PL_SET_ID_ERROR, __FILE__, __LINE__);
		if (p_scheduler_obj->p_players_list->id == p_process_instance->id)
			p_process_instance->p_owner = p_scheduler_obj->p_players_list;
		p_scheduler_obj->p_players_list = p_scheduler_obj->p_players_list->p_next;
	}
}

// static void	cw_exec_command(t_process *p_process_instance,
// 							t_corewar *p_game_obj)
// {
// 	if (!PR_CURRENT_COMMAND_I)
// 	{
// 		p_process_instance->cw_move_to(p_process_instance, 1);
// 		PR_NEAREST_CYCLE_I = p_game_obj->p_arena_obj->cycle + 1;
// 	}
// 	else if (PR_NEAREST_CYCLE_I == p_game_obj->p_arena_obj->cycle)
// 	{
// 		PR_CURRENT_COMMAND_I->cw_callback(p_game_obj);
// 		PR_CURRENT_COMMAND_I = NULL;
// 		PR_WAITING_TIME_I = 0;
// 		PR_NEAREST_CYCLE_I = p_game_obj->p_arena_obj->cycle + 1;
// 	}
// }

// static void	cw_set_command_time(t_process *p_process_instance,
// 									t_arena *p_arena_obj)
// {
// 	if (PR_CURRENT_COMMAND_I || AR_FIELD_O[PR_CURRENT_LOCATION_I] < CO_LIVE
// 	|| AR_FIELD_O[PR_CURRENT_LOCATION_I] > CO_AFF)
// 		return ;
// 	PR_CURRENT_COMMAND_I =
// 		PR_COMMAND_CONTAINER_I[AR_FIELD_O[PR_CURRENT_LOCATION_I]];
// 	PR_NEAREST_CYCLE_I = AR_CYCLE_O + PR_CURRENT_COMMAND_I->waiting_time - 1;
// 	p_process_instance->cw_save_pos(p_process_instance, PR_MAIN_SAVE);
// 	PR_ERROR_OCCURED_I = CW_FALSE;
// 	PR_OFFSET_I = 0;
// }

// static void	cw_set_owner(t_process *p_process_instance,
// 							t_player *p_player_list, int players_amount)
// {
// 	t_iter	iter;

// 	iter = CW_ITERATOR;
// 	while (++iter < players_amount)
// 	{
// 		if (p_player_list->id == PR_ID_I)
// 			PR_OWNER_I = p_player_list;
// 		p_player_list = p_player_list->p_next;
// 	}
// }

extern void	cw_process_prepare_functions_linker(t_process *p_process_instance)
{
	p_process_instance->cw_set_owner = cw_set_owner;
	p_process_instance->cw_exec_command = cw_exec_command;
	p_process_instance->cw_set_command_time = cw_set_command_time;
}
