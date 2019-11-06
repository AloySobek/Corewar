/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/06 21:13:00 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print(t_carriage *tree, int level)
{
	if (tree)
	{
		print(tree->p_left, level + 1);
		for (int i = 0; i < level; ++i)
			ft_printf("   ");
		ft_printf("%d\n", tree->id);
		print(tree->p_right, level + 1);
	}
}

int				main(int argc, char **argv)
{
	t_corewar	*p_game_obj;

	cw_create_instance_game(&p_game_obj);
	p_game_obj->cw_arena_obj_init(p_game_obj);
	p_game_obj->cw_scheduler_init(p_game_obj);
	p_game_obj->cw_player_obj_init(p_game_obj, argc, argv);
	p_game_obj->cw_carriage_obj_init(p_game_obj);
	p_game_obj->cw_command_obj_init(p_game_obj);
	p_game_obj->cw_write_code_to_memory(p_game_obj, p_game_obj->p_scheduler->pa_timeline[1]->p_root, MEM_SIZE / p_game_obj->p_scheduler->players_amount);
	p_game_obj->cw_introduce_players(p_game_obj, p_game_obj->p_scheduler->pa_timeline[1]->p_root, 0);
	p_game_obj->cw_start_game(p_game_obj);
	p_game_obj->cw_congratulations(p_game_obj);
	//p_game_obj->cw_destructor(&p_game_obj);
	return (CW_SUCCESS);
}
