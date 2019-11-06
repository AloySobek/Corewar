/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:40:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/06 21:27:44 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_main_checking(t_corewar *p_game_instance)
{
	;
}

static void		cw_start_game(t_corewar *p_game_instance)
{
	while (p_game_instance->carriages_amount > 0 && ++p_game_instance->p_arena_obj->cycle_amount)
	{

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
