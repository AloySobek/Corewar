/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_obj.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:15:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/11 19:23:24 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_GAME_OBJECT_H
# define CW_GAME_OBJECT_H

# include "cw_obj_container.h"

# define CW_COMMAND_AMOUNT	16 + 1

# define GA_SCHEDULER_I	p_game_instance->p_scheduler
# define GA_ID_I		p_game_instance->custom_id
# define GA_SC_LIST_I	GA_SCHEDULER_I->p_players_list
# define GA_SC_LISTR_I	GA_SCHEDULER_I->p_processes_list
# define GA_SC_PL_AM_I	GA_SCHEDULER_I->players_amount

# define GA_OBJ_NAME	"GAME"
# define GA_OBJ_ERROR	"Memory for GAME has not been allocated"
# define GA_KEY_ERROR	"Key in the args has not been recognize"

typedef struct			s_corewar
{
	t_flag				timeline_avl_tree_mode;
	t_flag				timeline_list_mode;
	t_flag				starting_cycle;
	t_flag				binary_output_mode;
	t_flag				dump_cycle;
	t_flag				custom_id;
	t_flag				aff_hide;
	t_flag				verbose;
	t_flag				ncurses;

	t_mark				last_check_cycle;
	t_counter			numerate_carriage;

	t_vis				*vis;
	t_scheduler			*p_scheduler;
	t_arena				*p_arena_obj;
	t_command			*pa_commands[CW_COMMAND_AMOUNT];

	t_process			*p_working_process;

	t_method			(*cw_constructor)						(t_corewar **);
	t_method			(*cw_arena_scheduler_command_obj_init)	(t_corewar *);
	t_method			(*cw_processes_obj_init)				(t_corewar *);
	t_method			(*cw_players_obj_init)					(t_corewar *, int, char **);
	t_method			(*cw_write_code_to_memory)				(t_corewar *);
	t_method			(*cw_introduce_players)					(t_corewar *);
	t_method			(*cw_congratulations)					(t_corewar *);
	t_method			(*cw_start_execution)					(t_corewar *);
	t_method			(*cw_destructor)						(t_corewar **);
}						t_corewar;

void					cw_create_instance_game		(t_corewar **pp_game_obj);
void					cw_game_process_linker		(t_corewar *p_game_instance);
void					cw_essence_init_linker		(t_corewar *p_game_instance);
void					cw_game_functions_linker	(t_corewar *p_game_instance);

#endif
