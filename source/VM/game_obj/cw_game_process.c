/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:40:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/12 14:31:42 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_start_execution(t_corewar *p_game_instance)
{
	while (GA_SC_PR_AM_I && ++p_game_instance->AR_CYCLE_O)
	{
		GA_SCHEDULER_I->cw_execution_processes(GA_SCHEDULER_I, p_game_instance);
		if (GA_ARENA_OBJ_I->cw_time_to_check(GA_ARENA_OBJ_I, GA_LAST_CHECK_I))
			GA_SCHEDULER_I->cw_deadline(GA_SCHEDULER_I, p_game_instance);
		if (GA_DUMP_I == p_game_instance->AR_CYCLE_O && GA_SC_PR_AM_I)
			GA_ARENA_OBJ_I->cw_print_field(GA_ARENA_OBJ_I);
	}
}

static void	cw_graphic_execution(t_corewar *p_game_instance)
{
	;
}

extern void	cw_game_process_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_start_execution = cw_start_execution;
	p_game_instance->cw_graphic_execution = cw_graphic_execution;
}
