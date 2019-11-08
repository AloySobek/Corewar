/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 16:14:01 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/08 16:15:16 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	cw_constructor(t_corewar **pp_game_instance)
{
	;
}

static void	cw_destructor(t_corewar **pp_game_instance)
{
	(*pp_game_instance)->p_arena_obj->cw_destructor(&(*pp_game_instance)->p_arena_obj);
	(*pp_game_instance)->p_scheduler->cw_destructor(&(*pp_game_instance)->p_scheduler);
	(*pp_game_instance)->cw_free_all_commands(*pp_game_instance);
	cr_vis_main(*pp_game_instance, V_CLEANUP);
	free(*pp_game_instance);
	*pp_game_instance = NULL;
}

extern void	cw_create_instance_game(t_corewar **pp_game_obj)
{
	if (!(*pp_game_obj = (t_corewar *)malloc(sizeof(t_corewar))))
		cw_error_catcher(CW_NOT_ALLOCATED, CW_GAME);
	ft_memset(*pp_game_obj, 0, sizeof(t_corewar));
	(*pp_game_obj)->cw_constructor = cw_constructor;
	(*pp_game_obj)->cw_destructor = cw_destructor;
	(*pp_game_obj)->cw_constructor(pp_game_obj);
	cw_game_process_linker(*pp_game_obj);
	cw_essence_init_linker(*pp_game_obj);
	cw_game_functions_linker(*pp_game_obj);
}
