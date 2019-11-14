/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_obj.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <dbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:15:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/14 16:01:44 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_GAME_OBJ_H
# define CW_GAME_OBJ_H

# include "cw_obj_container.h"

# define CW_COMMAND_AMOUNT	16 + 1

# define GA_DUMP_I			p_game_instance->dump_cycle
# define GA_LAST_CHECK_I	p_game_instance->last_check_cycle
# define GA_ARENA_OBJ_I		p_game_instance->p_arena_obj
# define GA_WORK_UNIT_I		p_game_instance->p_working_process
# define GA_ITERATOR_I		p_game_instance->custom_id
# define GA_SELLOUT_I		p_game_instance->sellout

# define GA_SCHEDULER_I		p_game_instance->p_scheduler
# define GA_ID_I			p_game_instance->custom_id
# define GA_SC_PL_I			GA_SCHEDULER_I->p_players_list
# define GA_SC_PR_I			GA_SCHEDULER_I->p_processes_list
# define GA_SC_PL_AM_I		GA_SCHEDULER_I->players_amount
# define GA_SC_PR_AM_I		GA_SCHEDULER_I->processes_amount
# define GA_TREE_TIME_I		p_game_instance->timeline_avl_tree_mode
# define GA_LIST_TIME_I		p_game_instance->timeline_list_mode

# define GA_SCHEDULER_O		p_game_obj->p_scheduler
# define GA_WORK_UNIT_O		p_game_obj->p_working_process
# define GA_ARENA_OBJ_O		p_game_obj->p_arena_obj
# define GA_ITERATOR_O		p_game_obj->custom_id
# define GA_SC_PL_AM_O		GA_SCHEDULER_O->players_amount
# define GA_SC_PL_O			GA_SCHEDULER_O->p_players_list
# define GA_SELLOUT_O		p_game_obj->sellout

# define GA_TREE_TIME_O		p_game_obj->timeline_avl_tree_mode
# define GA_LIST_TIME_O		p_game_obj->timeline_list_mode

# define GA_OBJ_NAME		"GAME"
# define GA_OBJ_ERROR		"Memory for GAME has not been allocated"
# define GA_KEY_ERROR		"Key in the args has not been recognize"
# define GA					 p_game_obj->AR_VALUE_BUF_3_O, GA_THIRD_ARG

# define GA_FIRST_ARG		GA_WORK_UNIT_O->args >> 6 & 0x03
# define GA_SECOND_ARG		GA_WORK_UNIT_O->args >> 4 & 0x03
# define GA_THIRD_ARG		GA_WORK_UNIT_O->args >> 2 & 0x03

# define GA_WRITING_MODE	1
# define GA_INTRO_MODE		-1
# define GA_SHOW_LIVES		1
# define GA_SHOW_CYCLES		2
# define GA_SHOW_OPER		4
# define GA_SHOW_DEATH		8

typedef struct			s_corewar
{
	t_flag		timeline_avl_tree_mode;
	t_flag		timeline_list_mode;
	t_flag		starting_cycle;
	t_flag		binary_output_mode;
	t_flag		dump_cycle;
	t_flag		custom_id;
	t_flag		aff_hide;
	t_flag		verbose;
	t_flag		ncurses;
	t_flag		sellout;
	t_flag		stealth;

	t_mark		last_check_cycle;
	t_counter	numerate_carriage;

	t_vis		*vis;
	t_scheduler	*p_scheduler;
	t_arena		*p_arena_obj;
	t_command	*pa_commands[CW_COMMAND_AMOUNT];

	t_process	*p_working_process;

	t_method	(*cw_constructor)			(struct s_corewar **);
	t_method	(*cw_arena_scheduler_command_obj_init)
											(struct s_corewar *);
	t_method	(*cw_processes_obj_init)	(struct s_corewar *);
	t_method	(*cw_players_obj_init)		(struct s_corewar *, int, char **);
	t_method	(*cw_write_code_to_memory)	(struct s_corewar *);
	t_method	(*cw_introduce_players)		(struct s_corewar *);
	t_method	(*cw_congratulations)		(struct s_corewar *);
	t_method	(*cw_start_execution)		(struct s_corewar *);
	t_method	(*cw_graphic_execution)		(struct s_corewar *);
	t_method	(*cw_usage)					(struct s_corewar *);
	t_method	(*cw_destructor)			(struct s_corewar **);
}						t_corewar;

void					cw_create_instance_game	(t_corewar **pp_game_obj);
void					cw_game_process_linker	(t_corewar *p_game_instance);
void					cw_essence_init_linker	(t_corewar *p_game_instance);
void					cw_game_functions_linker(t_corewar *p_game_instance);

#endif
