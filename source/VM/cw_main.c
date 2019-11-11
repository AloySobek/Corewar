/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/11 22:06:48 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **argv)
{
	t_corewar	*p_game_obj;

	cw_create_instance_game(&p_game_obj);
	p_game_obj->cw_arena_scheduler_command_obj_init(p_game_obj);
	p_game_obj->cw_players_obj_init(p_game_obj, argc, argv);
	p_game_obj->cw_processes_obj_init(p_game_obj);
	p_game_obj->cw_write_code_to_memory(p_game_obj);
	p_game_obj->cw_introduce_players(p_game_obj);
	p_game_obj->cw_start_execution(p_game_obj);
	p_game_obj->cw_congratulations(p_game_obj);
	//p_game_obj->cw_destructor(&p_game_obj);
	return (CW_SUCCESS);
}
