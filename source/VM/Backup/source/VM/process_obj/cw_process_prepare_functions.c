/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_prepare_functions.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:18:37 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 16:36:36 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_exec_command(t_process *p_process_instance, t_corewar *p_game_instance)
{
	if (!p_process_instance->p_current_command)
	{
		p_process_instance->cw_move_to(p_process_instance, 1);
		p_process_instance->nearest_cycle = p_game_instance->p_arena_obj->cycle + 1;
	}
	else if (p_process_instance->nearest_cycle == p_game_instance->p_arena_obj->cycle)
	{
		p_process_instance->p_current_command->cw_callback(p_game_instance);
		p_process_instance->p_current_command = NULL;
		p_process_instance->waiting_time = 0;
		p_process_instance->nearest_cycle = p_game_instance->p_arena_obj->cycle + 1;
	}
}

static void	cw_set_command_time(t_process *p_process_instance, t_arena *pArenaInstance)
{
	if (p_process_instance->p_current_command || pArenaInstance->p_field[p_process_instance->current_location] < CO_LIVE || pArenaInstance->p_field[p_process_instance->current_location] > CO_AFF)
		return ;
	p_process_instance->p_current_command = p_process_instance->pp_command_container[pArenaInstance->p_field[p_process_instance->current_location]];
	p_process_instance->nearest_cycle = pArenaInstance->cycle + p_process_instance->p_current_command->waiting_time - 1;
	p_process_instance->cw_save_pos(p_process_instance, PR_MAIN_SAVE);
	p_process_instance->error_ocurred = CW_FALSE;
	p_process_instance->offset = 0;
}

static void	cw_set_owner(t_process *p_process_instance, t_player *p_player_list, int players_amount)
{
	int	iter;

	iter = CW_ITERATOR;
	while (++iter < players_amount)
	{
		if (p_player_list->id == p_process_instance->id)
			p_process_instance->p_owner = p_player_list;
		p_player_list = p_player_list->p_next;
	}
}

extern void	cw_process_prepare_functions_linker(t_process *p_process_instance)
{
	p_process_instance->cw_set_owner = cw_set_owner;
	p_process_instance->cw_set_command_time = cw_set_command_time;
	p_process_instance->cw_exec_command = cw_exec_command;
}