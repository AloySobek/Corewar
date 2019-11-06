/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:41:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/06 17:18:02 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_arrange_units_on_field(t_corewar *p_game_instance)
{
	int		iter;
	int		player_location;
	int		memoryStep;
	int		codeIter;

	memoryStep = MEM_SIZE / p_game_instance->players_amount;
	iter = CW_ITERATOR;
	// while (++iter < p_game_instance->p_scheduler->p_distribution_stack->size)
	// {
	// 	p_game_instance->p_scheduler->p_distribution_stack->cw_rotate(p_game_instance->p_scheduler->p_distribution_stack);
	// 	codeIter = CW_BEGIN_FROM_ZERO;
	// 	player_location = memoryStep * iter;
	// 	p_game_instance->p_scheduler->p_distribution_stack->p_current_carriage->current_location = player_location;
	// 	while (player_location < memoryStep * iter + CHAMP_MAX_SIZE)
	// 		p_game_instance->p_arena_obj->p_field[player_location++] = p_game_instance->p_scheduler->p_distribution_stack->p_current_carriage->p_owner->p_code[codeIter++];
	// }
}

static void	cw_congratulations(t_corewar *p_game_instance)
{
	if (p_game_instance->visualizator)
		cr_vis_winner(p_game_instance);
	else
		ft_printf("Contestant %d, \"%s\", has won !\n",
		p_game_instance->p_arena_obj->p_last_survivor->id,
		p_game_instance->p_arena_obj->p_last_survivor->p_name);
}

static void	cw_introduce_players(t_corewar *p_game_instance)
{
	int		iter;

	iter = CW_ITERATOR;
	ft_printf("Introducing contestants...\n");
	// while (++iter < p_game_instance->carriages_amount)
	// {
	// 	p_game_instance->p_scheduler->p_distribution_stack->cw_reverse_rotate(p_game_instance->p_scheduler->p_distribution_stack);
	// 	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
	// 	p_game_instance->p_scheduler->p_distribution_stack->p_current_carriage->p_owner->id,
	// 	p_game_instance->p_scheduler->p_distribution_stack->p_current_carriage->p_owner->code_size,
	// 	p_game_instance->p_scheduler->p_distribution_stack->p_current_carriage->p_owner->p_name,
	// 	p_game_instance->p_scheduler->p_distribution_stack->p_current_carriage->p_owner->p_comment);
	// }
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
	p_game_instance->cw_arrange_units_on_field	= cw_arrange_units_on_field;
	p_game_instance->cw_free_all_commands		= cw_free_all_commands;
	p_game_instance->cw_introduce_players		= cw_introduce_players;
	p_game_instance->cw_congratulations			= cw_congratulations;
}