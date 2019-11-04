/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/04 19:53:01 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				main(int argc, char **argv)
{
	t_corewar	*p_game_obj;
	t_carriage	*tmp;

	cw_create_instance_game(&p_game_obj);
	p_game_obj->cw_arena_obj_init(p_game_obj);
	p_game_obj->cw_scheduler_init(p_game_obj);
	p_game_obj->cw_player_obj_init(p_game_obj, argc, argv);
	p_game_obj->cw_carriage_obj_init(p_game_obj);
	p_game_obj->cw_command_obj_init(p_game_obj);
	p_game_obj->cw_arrange_units_on_field(p_game_obj);
	p_game_obj->cw_introduce_players(p_game_obj);
	for (int i = 0; i < p_game_obj->carriages_amount; ++i)
	{
		p_game_obj->p_scheduler->p_distribution_stack->cw_pop(p_game_obj->p_scheduler->p_distribution_stack, &tmp, NULL);
		p_game_obj->p_scheduler->p_waiting_queue->cw_quant_enqueue(p_game_obj->p_scheduler->p_waiting_queue, tmp);
	}
	//p_game_obj->p_scheduler->p_waiting_queue->cw_dequeue(p_game_obj->p_scheduler->p_waiting_queue, &tmp);
	//tmp->nearest_cycle = 100;
	//p_game_obj->p_scheduler->p_waiting_queue->cw_quant_enqueue(p_game_obj->p_scheduler->p_waiting_queue, tmp);
	//p_game_obj->p_scheduler->p_waiting_queue->cw_print_content(p_game_obj->p_scheduler->p_waiting_queue);
	//exit(1);
	p_game_obj->cw_start_game(p_game_obj);
	p_game_obj->cw_congratulations(p_game_obj);
	//p_game_obj->cw_destructor(&p_game_obj);
	return (CW_SUCCESS);
}
