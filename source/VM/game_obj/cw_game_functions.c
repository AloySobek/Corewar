/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:41:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/08 20:58:45 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_write_code_to_memory(t_corewar *p_game_instance, t_process *p_process_obj, int memory_step)
{
	int		player_location;
	int		code_iter;

	if (p_process_obj)
	{
		p_game_instance->cw_write_code_to_memory(p_game_instance, p_process_obj->p_left, memory_step);
		code_iter = CW_ITERATOR;
		player_location = memory_step * (p_process_obj->p_owner->id - 1);
		p_process_obj->current_location = player_location;
		while (player_location < memory_step * (p_process_obj->p_owner->id - 1) + CHAMP_MAX_SIZE)
			p_game_instance->p_arena_obj->p_field[player_location++] = p_process_obj->p_owner->p_code[++code_iter];
		p_game_instance->cw_write_code_to_memory(p_game_instance, p_process_obj->p_right, memory_step);
	}
}

static void	cw_congratulations(t_corewar *p_game_instance)
{
	if (p_game_instance->visualizator)
		cr_vis_winner(p_game_instance);
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
		p_game_instance->p_arena_obj->p_winner->id,
		p_game_instance->p_arena_obj->p_winner->p_name);
}

static void	cw_introduce_players(t_corewar *p_game_instance, t_process *p_introducing_carriage, int level)
{
	int		iter;

	iter = CW_ITERATOR;
	if (!level)
		ft_printf("Introducing contestants...\n");
	if (p_introducing_carriage)
	{
		p_game_instance->cw_introduce_players(p_game_instance, p_introducing_carriage->p_left, level + 1);
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		p_introducing_carriage->p_owner->id,
		p_introducing_carriage->p_owner->code_size,
		p_introducing_carriage->p_owner->p_name,
		p_introducing_carriage->p_owner->p_comment);
		p_game_instance->cw_introduce_players(p_game_instance, p_introducing_carriage->p_right, level + 1);
	}
}

static void	cw_free_all_commands(t_corewar *p_game_instance)
{
	int		iter;

	iter = CW_BEGIN_FROM_ZERO;
	while (++iter < CW_COMMAND_AMOUNT)
		p_game_instance->pa_commands[iter]->cw_destructor(&p_game_instance->pa_commands[iter]);
}

extern void	cw_game_functions_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_write_code_to_memory	= cw_write_code_to_memory;
	p_game_instance->cw_free_all_commands		= cw_free_all_commands;
	p_game_instance->cw_introduce_players		= cw_introduce_players;
	p_game_instance->cw_congratulations			= cw_congratulations;
}