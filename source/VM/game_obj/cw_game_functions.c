/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 15:41:14 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/12 15:32:31 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_write_code_to_memory(t_corewar *p_game_instance)
{
	t_iter	pl_lo;
	t_iter	code_iter;
	t_iter	iter;

	if (p_game_instance->timeline_avl_tree_mode)
		;
	else if (p_game_instance->timeline_list_mode)
		;
	else
	{
		iter = CW_ITERATOR;
		while (++iter < p_game_instance->p_scheduler->processes_amount)
		{
			pl_lo = MEM_SIZE / GA_SC_PL_AM_I * (GA_SC_PR_I->p_owner->id - 1);
			code_iter = CW_ITERATOR;
			GA_SC_PR_I->current_location = pl_lo;
			while (pl_lo < MEM_SIZE / GA_SC_PL_AM_I *
			(GA_SC_PR_I->p_owner->id - 1) + CHAMP_MAX_SIZE)
				p_game_instance->p_arena_obj->p_field[pl_lo++] =
					GA_SC_PR_I->p_owner->p_code[++code_iter];
			GA_SC_PR_I = GA_SC_PR_I->p_next;
		}
	}
}

static void	cw_congratulations(t_corewar *p_game_instance)
{
	ft_printf("Contestant %d, \"%s\", has won !\n",
	p_game_instance->p_arena_obj->p_winner->id,
	p_game_instance->p_arena_obj->p_winner->p_name);
}

static void	cw_introduce_players(t_corewar *p_game_instance)
{
	t_iter	iter;

	iter = CW_ITERATOR;
	if (p_game_instance->timeline_avl_tree_mode)
		;
	else if (p_game_instance->timeline_avl_tree_mode)
		;
	else
	{
		ft_printf("Introducing contestants...\n");
		while (++iter < p_game_instance->p_scheduler->processes_amount)
		{
			p_game_instance->p_scheduler->p_processes_list =
			p_game_instance->p_scheduler->p_processes_list->p_prev;
			ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
			p_game_instance->p_scheduler->p_processes_list->p_owner->id,
			p_game_instance->p_scheduler->p_processes_list->p_owner->code_size,
			p_game_instance->p_scheduler->p_processes_list->p_owner->p_name,
			p_game_instance->p_scheduler->p_processes_list->p_owner->p_comment);
		}
	}
}

extern void	cw_game_functions_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_write_code_to_memory = cw_write_code_to_memory;
	p_game_instance->cw_introduce_players = cw_introduce_players;
	p_game_instance->cw_congratulations = cw_congratulations;
}
