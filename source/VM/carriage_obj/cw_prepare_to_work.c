/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_prepare_to_work.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:18:37 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/03 19:37:28 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	cw_reduce_waiting_time(t_carriage *pCarraigeInstance)
{
	if (pCarraigeInstance->waiting_time > 0)
		pCarraigeInstance->waiting_time -= 1;
}

void	cw_exec_command(t_carriage *p_carriage_instance, t_corewar *p_game_instance)
{
	if (!p_carriage_instance->p_current_command)
		p_carriage_instance->cw_move_to(p_carriage_instance, 1);
	else if (!p_carriage_instance->waiting_time)
	{
		p_carriage_instance->p_current_command->cw_callback(p_game_instance);
		p_carriage_instance->p_current_command = NULL;
		p_carriage_instance->waiting_time = 0;
	}
}

void	cw_set_command_time(t_carriage *p_carriage_instance, t_arena *pArenaInstance)
{
	if (pArenaInstance->p_field[p_carriage_instance->current_location] < CW_LIVE || pArenaInstance->p_field[p_carriage_instance->current_location] > CW_AFF)
		return ;
	p_carriage_instance->p_current_command = p_carriage_instance->pp_command_container[pArenaInstance->p_field[p_carriage_instance->current_location]];
	p_carriage_instance->nearest_cycle = pArenaInstance->cycle_amount + p_carriage_instance->p_current_command->waiting_time - 1;
	p_carriage_instance->cw_save_pos(p_carriage_instance, CW_MAIN_SAVE);
	p_carriage_instance->error_ocurred = CW_FALSE;
	p_carriage_instance->offset = 0;
}

void	cw_set_owner(t_carriage *p_carriage_instance, t_player *p_player_list, int players_amount)
{
	int	iter;

	iter = CW_ITERATOR;
	while (++iter < players_amount)
	{
		if (p_player_list->id == p_carriage_instance->id)
			p_carriage_instance->p_owner = p_player_list;
		p_player_list = p_player_list->p_next;
	}
}