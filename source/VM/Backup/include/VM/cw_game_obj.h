/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_game_obj.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:15:38 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/09 16:32:39 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_GAME_OBJECT_H
# define CW_GAME_OBJECT_H

# include "cw_obj_container.h"

# define CW_COMMAND_AMOUNT	16 + 1

typedef struct			s_corewar
{
	t_flag				starting_cycle;
	t_flag				binary_mode;
	t_flag				cycle_dump;
	t_flag				load_dump;
	t_flag				custom_id;
	t_flag				aff_hide;
	t_flag				verbose;
	t_flag				stealth;
	t_flag				ncurses;

	t_counter			players_amount;
	t_counter			commands_amount;
	t_counter			carriages_amount;

	t_mark				last_check_cycle;
	t_mark				numerate_carriage;

	t_process			*p_working_process;
	t_scheduler			*p_scheduler;
	t_command			*pa_commands[CW_COMMAND_AMOUNT];
	t_arena				*p_arena_obj;
	t_vis				*vis;

	t_process			*p_process_obj;
	t_player			*p_player_obj;

	t_method			(*cw_constructor)			(t_corewar **);
	t_method			(*cw_keys_parse)			(t_corewar *, char **, int, int);
	t_method			(*cw_scheduler_init)		(t_corewar *);
	t_method			(*cw_process_obj_init)		(t_corewar *);
	t_method			(*cw_command_obj_init)		(t_corewar *);
	t_method			(*cw_player_obj_init)		(t_corewar *, int, char **);
	t_method			(*cw_arena_obj_init)		(t_corewar *);
	t_method			(*cw_free_all_commands)		(t_corewar *);
	t_method			(*cw_write_code_to_memory)	(t_corewar *, t_process *, int);
	t_method			(*cw_introduce_players)		(t_corewar *, t_process *, int);
	t_method			(*cw_congratulations)		(t_corewar *);
	t_method			(*cw_main_checking)			(t_corewar *);
	t_method			(*cw_start_game)			(t_corewar *);
	t_method			(*cw_start_graphic_game)	(t_corewar *);
	t_method			(*cw_destructor)			(t_corewar **);
}						t_corewar;

void					cw_create_instance_game		(t_corewar **pp_game_obj);
void					cw_game_process_linker		(t_corewar *p_game_instance);
void					cw_essence_init_linker		(t_corewar *p_game_instance);
void					cw_game_functions_linker	(t_corewar *p_game_instance);

#endif
