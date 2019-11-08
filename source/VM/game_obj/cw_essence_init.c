/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_essence_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:39:29 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/08 20:24:49 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		cw_command_obj_init(t_corewar *p_game_instance)
{
	t_command	*pCommandObj;
	int			iter;

	iter = CW_BEGIN_FROM_ONE;
	while (iter < CW_COMMAND_AMOUNT)
	{
		cw_create_instance_command(&pCommandObj);
		pCommandObj->cw_recognize(pCommandObj, iter);
		p_game_instance->pa_commands[iter] = pCommandObj;
		++iter;
	}
}

static void		cw_carriage_obj_init(t_corewar *p_game_instance)
{
	t_process	*p_process_obj;
	int			iter;

	iter = CW_ITERATOR;
	while (++iter < p_game_instance->p_scheduler->players_amount)
	{
		cw_create_instance_process(&p_process_obj);
		p_process_obj->id = ++p_game_instance->carriages_amount;
		p_process_obj->pp_command_container = p_game_instance->pa_commands;
		p_process_obj->cw_set_owner(p_process_obj, p_game_instance->p_scheduler->p_player_obj, p_game_instance->players_amount);
		p_process_obj->cw_write_owner_id_to_reg(p_process_obj);
		p_game_instance->p_scheduler->cw_insert_process(p_game_instance->p_scheduler, p_process_obj, 1);
		p_game_instance->p_scheduler->cw_list_process(p_game_instance->p_scheduler, p_process_obj);
	}
	p_game_instance->numerate_carriage = p_game_instance->carriages_amount;
}

static void		cw_keys_parse(t_corewar *p_game_instance, char **argv, int argc, int iter)
{
	while (*++(argv[iter]))
		if (*(argv[iter]) == 'n' && iter + 1 < argc && (p_game_instance->custom_id = ft_atoi(argv[iter + 1])) > CW_MIN_PLAYERS && p_game_instance->custom_id < CW_MAX_PLAYERS)
			;
		else if (*(argv[iter]) == 'd' && iter + 1 < argc)
			p_game_instance->cycle_dump = ft_atoi(argv[iter + 1]);
		else if (*(argv[iter]) == 's' && iter + 1 < argc)
			p_game_instance->visual_cycle = ft_atoi(argv[iter + 1]);
		else if (*(argv[iter]) == 'v' && iter + 1 < argc)
			p_game_instance->verbose = ft_atoi(argv[iter + 1]);
		else if (*(argv[iter]) == 'g')
			p_game_instance->visualizator = CW_TRUE;
		else if (*(argv[iter]) == 'b')
			p_game_instance->binary_mode = CW_TRUE;
		else if (*(argv[iter]) == 'a')
			p_game_instance->aff_hide = CW_FALSE;
		else if (ft_strcmp(argv[iter], "-stealth"))
			p_game_instance->stealth = CW_TRUE;
		else
			cw_error_catcher(CW_NOT_VALID_KEY, "Not valid Key");
}

static void		cw_player_obj_init(t_corewar *p_game_instance, int argc, char **argv)
{
	t_player	*p_player_obj;
	int			standartId;
	int			iter;
	int			busyByte;

	standartId	= 0;
	busyByte	= CW_ALL_FREE;
	iter		= CW_BEGIN_FROM_ZERO;
	while (++iter < argc)
		if (*(argv[iter]) == CW_KEY)
		{
			p_game_instance->cw_keys_parse(p_game_instance, argv, argc, iter);
			if (p_game_instance->load_dump || p_game_instance->verbose || p_game_instance->visual_cycle || p_game_instance->custom_id)
				++iter;
		}
		else if (++p_game_instance->players_amount)
		{
			cw_create_instance_player		(&p_player_obj);
			p_player_obj->cw_read_file		(p_player_obj, argv[iter]);
			p_player_obj->cw_self_build		(p_player_obj);
			p_player_obj->cw_self_validate	(p_player_obj);
			if (p_game_instance->custom_id)
				p_player_obj->cw_set_id(p_player_obj, &busyByte, p_game_instance->custom_id, CW_TRUE);
			p_game_instance->p_scheduler->cw_insert_player(p_game_instance->p_scheduler, p_player_obj);
			p_game_instance->custom_id = 0;
		}
	if (p_game_instance->players_amount < 1 || p_game_instance->players_amount > 4)
		cw_error_catcher(CW_INVALID_PLAYERS, CW_PLAYER);
	iter = CW_ITERATOR;
	while (++iter < p_game_instance->p_scheduler->players_amount)
	{
		if (!p_game_instance->p_scheduler->p_player_obj->id)
			p_game_instance->p_scheduler->p_player_obj->cw_set_id(p_game_instance->p_scheduler->p_player_obj, &busyByte, 1, CW_FALSE);
		p_game_instance->p_scheduler->p_player_obj = p_game_instance->p_scheduler->p_player_obj->p_next;
	}
}

static void		cw_scheduler_init(t_corewar *p_game_instance)
{
	t_scheduler	*p_scheduler;

	cw_create_instance_scheduler(&p_scheduler);
	p_scheduler->cw_queues_init(p_scheduler, p_game_instance);
	p_game_instance->p_scheduler = p_scheduler;
}

static void		cw_arena_obj_init(t_corewar *p_game_instance)
{
	t_arena		*p_arena_obj;

	cw_create_instance_arena(&p_arena_obj);
	p_arena_obj->cw_buffer_init(p_arena_obj);
	p_game_instance->p_arena_obj = p_arena_obj;
}

extern void		cw_essence_init_linker(t_corewar *p_game_instance)
{
	p_game_instance->cw_carriage_obj_init	= cw_carriage_obj_init;
	p_game_instance->cw_command_obj_init	= cw_command_obj_init;
	p_game_instance->cw_player_obj_init		= cw_player_obj_init;
	p_game_instance->cw_arena_obj_init		= cw_arena_obj_init;
	p_game_instance->cw_scheduler_init		= cw_scheduler_init;
	p_game_instance->cw_keys_parse			= cw_keys_parse;
}