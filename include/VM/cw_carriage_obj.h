/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_carriage_obj.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 17:18:15 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/08 20:29:05 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_CARRIAGE_OBJECT_H
# define CW_CARRIAGE_OBJECT_H

# include "cw_obj_container.h"

# define PR_ID_I				p_process_instance->id
# define PR_CARRY_I				p_process_instance->carry
# define PR_ODOMETER_I			p_process_instance->odometer
# define PR_SAVE_POINT_I		p_process_instance->save_point
# define PR_WAITING_TIME		p_process_instance->waiting_time
# define PR_ADDIT_ODOMETER_I	p_process_instance->addit_odometer
# define PR_LAST_SPEAK_CYCLE_I	p_process_instance->last_speak_cycle
# define PR_ADDIT_SAVE_POINT_I	p_process_instance->addit_save_point
# define PR_CURRENT_LOCATION_I	p_process_instance->current_location
# define PR_CURRENT_REGISTER_I	p_process_instance->current_register
# define PR_ERROR_OCCURED_I		p_process_instance->error_occured

# define PR_OBJECT_NAME			"PROCESS"
# define PR_OBJECT_ERROR		"Memory for PROCESS has not been allocated"
# define PR_SAVE_ERROR			"While trying to save position"
# define PR_RETURN_ERROR		"While trying to return at start position"

# define PR_MAIN_SAVE			1
# define PR_ADDIT_SAVE			2

typedef struct			s_process
{
	t_mark				id;
	t_mark				carry;
	t_counter			odometer;
	t_mark				save_point;
	t_counter			waiting_time;
	t_counter			addit_odometer;
	t_mark				last_speak_cycle;
	t_mark				addit_save_point;
	t_mark				current_location;
	char				current_register;
	t_mark				error_ocurred;
	t_attribute			args;
	t_mark				offset;
	t_mark				nearest_cycle;
	t_mark				kill;

	int					height;

	t_byte				*p_registers;

	struct s_carriage	*p_next;
	struct s_carriage	*p_prev;

	struct s_carriage	*p_right;
	struct s_carriage	*p_left;

	t_command			**pp_command_container;
	t_command			*p_current_command;
	t_player			*p_owner;
	t_corewar			*game_ref;

	t_method			(*cw_constructor)				(struct s_process **);
	t_method			(*cw_save_pos)					(struct s_process *, t_flag);
	t_method			(*cw_exec_command)				(struct s_process *, t_corewar *);
	t_method			(*cw_set_command_time)			(struct s_process *, t_arena *);
	t_method			(*cw_parse_types)				(struct s_process *, t_arena *);
	t_method			(*cw_move_to)					(struct s_process *, int);
	t_method 			(*cw_carriage_return)			(struct s_process *, int);
	t_method			(*cw_set_owner)					(struct s_process *, t_player *, int);
	t_method			(*cw_conversion_value_to_bytes)	(struct s_process *, t_buffer *, int);
	t_method			(*cw_conversion_bytes_to_value)	(struct s_process *, t_buffer *, int);
	t_method			(*cw_write_operation)			(struct s_process *, t_arena *, t_buffer *, int);
	t_method			(*cw_read_operation)			(struct s_process *, t_arena *, t_buffer *, int);
	t_method			(*cw_check_carry)				(struct s_process *);
	t_method 			(*cw_write_owner_id_to_reg)		(struct s_process *);
	t_method			(*cw_copy_reg)					(struct s_process *, t_process *);
	t_method			(*cw_reg_check)					(struct s_process *, t_arena *, int, int *);
	t_method			(*cw_destructor)				(struct s_process **);
}						t_process;

void					cw_reg_check(t_process *p_process_instance, t_arena *p_arena_obj, int type, int *);
void					cw_copy_reg(t_process *p_process_instance, t_process *p_copying_carriage);
void					cw_write_owner_id_to_reg(t_process *p_process_instance);
void					cw_check_carry(t_process *p_process_instance);
void					cw_conversion_value_to_bytes(t_process *pCarraigeInstance, t_buffer *pBufferObj, int type);
void					cw_conversion_bytes_to_value(t_process *pCarraigeInstance, t_buffer *pBufferObj, int type);
void					cw_write_operation(t_process *p_process_instance, t_arena *p_arena_obj, t_buffer *pBufferObj, int inputArg);
void					cw_read_operation(t_process *p_process_instance, t_arena *p_arena_obj, t_buffer *pBufferObj, int inputArg);
void					cw_reduce_waiting_time(t_process *pCarraigeInstance);
void					cw_exec_command(t_process *p_process_instance, t_corewar *p_game_instance);
void					cw_set_command_time(t_process *p_process_instance, t_arena *pArenaInstance);
void					cw_set_owner(t_process *p_process_instance, t_player *pPlayerList, int playersAmount);

void					cw_process_movements_functions_linker(t_process *p_process_instance);

#endif
