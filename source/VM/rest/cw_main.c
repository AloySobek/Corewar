/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:09:41 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/06 18:35:12 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print(t_carriage *test, int level)
{
	if (test)
	{
		print(test->p_left, level + 1);
		for (int i = 0; i < level; ++i )
			ft_printf("   ");
		printf("%d\n", test->id);
		print(test->p_right, level + 1);
	}
}

int				main(int argc, char **argv)
{
	t_corewar	*p_game_obj;
	t_queue		*test;
	t_carriage	*new;
	t_carriage	*new1;
	t_carriage	*new2;
	t_carriage	*new3;
	t_carriage	*new4;
	t_carriage	*new5;
	t_carriage	*new6;
	t_carriage	*new7;
	t_carriage	*new8;

	cw_create_instance_carriage(&new);
	cw_create_instance_carriage(&new1);
	cw_create_instance_carriage(&new2);
	cw_create_instance_carriage(&new3);
	cw_create_instance_carriage(&new4);
	cw_create_instance_carriage(&new5);
	cw_create_instance_carriage(&new6);
	cw_create_instance_carriage(&new7);
	cw_create_instance_carriage(&new8);
	cw_create_instance_queue(&test);
	new->id = 0;
	new1->id = 1;
	new2->id = 2;
	new3->id = 3;
	new4->id = 4;
	new5->id = 5;
	new6->id = -6;
	new7->id = -7;
	new8->id = -8;

	cw_create_instance_game(&p_game_obj);
	p_game_obj->cw_arena_obj_init(p_game_obj);
	p_game_obj->cw_scheduler_init(p_game_obj);
	test->p_root = test->cw_enqueue(test, test->p_root, new);
	test->p_root = test->cw_enqueue(test, test->p_root, new1);
	test->p_root = test->cw_enqueue(test, test->p_root, new2);
	test->p_root = test->cw_enqueue(test, test->p_root, new3);
	test->p_root = test->cw_enqueue(test, test->p_root, new4);
	test->p_root = test->cw_enqueue(test, test->p_root, new5);
	test->p_root = test->cw_enqueue(test, test->p_root, new6);
	test->p_root = test->cw_enqueue(test, test->p_root, new7);
	test->p_root = test->cw_enqueue(test, test->p_root, new8);
	print(test->p_root, 0);
	exit(1);
	p_game_obj->cw_player_obj_init(p_game_obj, argc, argv);
	p_game_obj->cw_carriage_obj_init(p_game_obj);
	p_game_obj->cw_command_obj_init(p_game_obj);
	p_game_obj->cw_arrange_units_on_field(p_game_obj);
	p_game_obj->cw_introduce_players(p_game_obj);
	p_game_obj->cw_start_game(p_game_obj);
	p_game_obj->cw_congratulations(p_game_obj);
	//p_game_obj->cw_destructor(&p_game_obj);
	return (CW_SUCCESS);
}
