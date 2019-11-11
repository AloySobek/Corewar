/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_process_read_write_functions.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 16:10:45 by vrichese          #+#    #+#             */
/*   Updated: 2019/11/11 16:05:18 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		cw_write_operation(t_process *p_carriage_instance, t_arena *p_arena_obj, t_buffer *pBufferObj, int inputArg)
{
	if (inputArg == CW_REG_CODE)
	{
		p_carriage_instance->current_register = p_arena_obj->p_field[p_carriage_instance->current_location] - 1;
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
			p_carriage_instance->p_registers[i + p_carriage_instance->current_register * CW_REG_SIZE] = pBufferObj->p_data[i];
		p_carriage_instance->cw_move_to(p_carriage_instance, CW_REG_CODE_SIZE);
	}
	else if (inputArg == CW_IND_CODE)
	{
		ft_memset(p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data, 0, CW_REG_SIZE);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF], CW_SHORT);
		if (p_carriage_instance->p_current_command->id != CO_LLD)
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
		p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= MEM_SIZE;
		p_carriage_instance->cw_save_pos(p_carriage_instance, PR_ADDIT_SAVE);
		p_carriage_instance->cw_move_to	(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value - p_carriage_instance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
		{
			p_arena_obj->p_field[p_carriage_instance->current_location] = pBufferObj->p_data[i];
			//if (p_carriage_instance->game_ref->visualizator)
			//	cr_vis_putx(pBufferObj->p_data[i], p_carriage_instance->current_location, p_carriage_instance->p_owner->id, 0, p_carriage_instance->game_ref);
		}
		p_carriage_instance->cw_carriage_return(p_carriage_instance, PR_ADDIT_SAVE);
	}
}

void	cw_read_operation(t_process *p_carriage_instance, t_arena *p_arena_obj, t_buffer *pBufferObj, int inputArg)
{
	if (inputArg == CW_REG_CODE)
	{
		p_carriage_instance->current_register = p_arena_obj->p_field[p_carriage_instance->current_location] - 1;
		ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
			pBufferObj->p_data[i] = p_carriage_instance->p_registers[i + p_carriage_instance->current_register * CW_REG_SIZE];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, pBufferObj, CW_INT);
		p_carriage_instance->cw_move_to(p_carriage_instance, CW_REG_CODE_SIZE);
	}
	else if (inputArg == CW_DIR_CODE)
	{
		ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
		for (int i = 4 - p_carriage_instance->p_current_command->dir_size; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			pBufferObj->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, pBufferObj, 4 - p_carriage_instance->p_current_command->dir_size);
	}
	else if (inputArg == CW_IND_CODE)
	{
		ft_memset(p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data, 0, CW_REG_SIZE);
		ft_memset(pBufferObj->p_data, 0, CW_REG_SIZE);
		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF], CW_SHORT);
		if (p_carriage_instance->p_current_command->id != CO_LLD)
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
			p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value %= MEM_SIZE;
		p_carriage_instance->cw_save_pos(p_carriage_instance, PR_ADDIT_SAVE);
		p_carriage_instance->cw_move_to(p_carriage_instance, p_arena_obj->pa_buffer_set[CW_SYSTEM_BUF]->s_types.short_value - p_carriage_instance->odometer);
		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_carriage_instance->cw_move_to(p_carriage_instance, 1))
			pBufferObj->p_data[i] = p_arena_obj->p_field[p_carriage_instance->current_location];
		p_carriage_instance->cw_conversion_bytes_to_value(p_carriage_instance, pBufferObj, CW_INT);
		p_carriage_instance->cw_carriage_return(p_carriage_instance, PR_ADDIT_SAVE);
	}
}

// static void	cw_write_operation(t_process *p_process_instance, t_arena *p_arena_obj, t_buffer *p_buffer_obj, int input_arg)
// {
// 	t_iter	i;

// 	i = CW_ITERATOR;
// 	if (input_arg == CW_REG_CODE)
// 	{
// 		PR_CURRENT_REGISTER_I = AR_FIELD_O[PR_CURRENT_LOCATION_I] - 1;
// 		while (++i < CW_REG_SIZE)
// 			PR_REGISTERS_I[i + PR_CURRENT_REGISTER_I * CW_REG_SIZE] = BU_DATA_O[i];
// 		p_process_instance->cw_move_to(p_process_instance, CW_REG_CODE_SIZE);
// 	}
// 	else if (input_arg == CW_IND_CODE)
// 	{
// 		AR_BUFFERS_O[CW_SYSTEM_BUF]->cw_erase_data(AR_BUFFERS_O[CW_SYSTEM_BUF]);
// 		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
// 			AR_BUFFERS_O[CW_SYSTEM_BUF]->p_data[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// 		p_process_instance->cw_conversion(p_process_instance, AR_BUFFERS_O[CW_SYSTEM_BUF], CW_SHORT, PR_BYTE);
// 		if (p_process_instance->p_current_command->id != CO_LLD)
// 			AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
// 		AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value %= MEM_SIZE;
// 		p_process_instance->cw_save_pos(p_process_instance, PR_ADDIT_SAVE);
// 		p_process_instance->cw_move_to	(p_process_instance, AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value - p_process_instance->odometer);
// 		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
// 			p_arena_obj->p_field[PR_CURRENT_LOCATION_I] = BU_DATA_O[i];
// 		p_process_instance->cw_carriage_return(p_process_instance, PR_ADDIT_SAVE);
// 	}
// 	else
// 		cw_error_catcher(PR_OBJECT_NAME, PR_MEMORY_ERROR, __FILE__, __LINE__);
// }

// // static void	cw_ind_write_handle(t_process *p_process_instance,
// // 						t_arena *p_arena_obj, t_buffer *p_buffer_obj, t_iter i)
// // {
// // 	AR_SYSTEM_BUF_O->cw_erase_data(AR_SYSTEM_BUF_O);
// // 	i = CW_SHORT - 1;
// // 	while (++i < CW_REG_SIZE)
// // 	{
// // 		AR_SYSTEM_BUF_O->p_data[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// // 		p_process_instance->cw_move_to(p_process_instance, 1);
// // 	}
// // 	p_process_instance->cw_conversion(p_process_instance,
// // 		AR_SYSTEM_BUF_O, CW_SHORT, PR_BYTE);
// // 	if (PR_CURRENT_COMMAND_I->id != CO_LLD)
// // 		AR_SYSTEM_BUF_O->s_types.short_value %= IDX_MOD;
// // 	AR_SYSTEM_BUF_O->s_types.short_value %= MEM_SIZE;
// // 	p_process_instance->cw_save_pos(p_process_instance, PR_ADDIT_SAVE);
// // 	p_process_instance->cw_move_to(p_process_instance,
// // 		AR_SYSTEM_BUF_O->s_types.short_value - PR_ODOMETER_I);
// // 	i = CW_ITERATOR;
// // 	while (++i < CW_REG_SIZE)
// // 	{
// // 		AR_FIELD_O[PR_CURRENT_LOCATION_I] = BU_DATA_O[i];
// // 		p_process_instance->cw_move_to(p_process_instance, 1);
// // 	}
// // 	p_process_instance->cw_carriage_return(p_process_instance, PR_ADDIT_SAVE);
// // }

// // static void	cw_write_operation(t_process *p_process_instance,
// // 					t_arena *p_arena_obj, t_buffer *p_buffer_obj, int input_arg)
// // {
// // 	t_iter	i;

// // 	if (input_arg == CW_REG_CODE)
// // 	{
// // 		PR_CURRENT_REGISTER_I = AR_FIELD_O[PR_CURRENT_LOCATION_I] - 1;
// // 		i = CW_ITERATOR;
// // 		while (++i < CW_REG_SIZE)
// // 			PR_REGISTERS_I[i + PR_CURRENT_REGISTER_I * CW_REG_SIZE] = BU_DATA_O[i];
// // 		p_process_instance->cw_move_to(p_process_instance, CW_REG_CODE_SIZE);
// // 	}
// // 	else if (input_arg == CW_IND_CODE)
// // 		cw_ind_write_handle(p_process_instance, p_arena_obj, p_buffer_obj, i);
// // 	else
// // 		cw_error_catcher(PR_OBJECT_NAME, PR_MEMORY_ERROR, __FILE__, __LINE__);
// // }

// // static void	cw_ind_read_handle(t_process *p_process_instance,
// // 						t_arena *p_arena_obj, t_buffer *p_buffer_obj, t_iter i)
// // {
// // 	AR_BUFFERS_O[CW_SYSTEM_BUF]->cw_erase_data(AR_BUFFERS_O[CW_SYSTEM_BUF]);
// // 	i = CW_SHORT - 1;
// // 	while (++i < CW_REG_SIZE)
// // 	{
// // 		AR_SYSTEM_BUF_O->p_data[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// // 		p_process_instance->cw_move_to(p_process_instance, 1);
// // 	}
// // 	p_process_instance->cw_conversion(p_process_instance, AR_SYSTEM_BUF_O, CW_SHORT, PR_BYTE);
// // 	if (PR_CURRENT_COMMAND_I->id != CO_LLD)
// // 		AR_SYSTEM_BUF_O->s_types.short_value %= IDX_MOD;
// // 		AR_SYSTEM_BUF_O->s_types.short_value %= MEM_SIZE;
// // 	p_process_instance->cw_save_pos(p_process_instance, PR_ADDIT_SAVE);
// // 	p_process_instance->cw_move_to(p_process_instance, AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value - p_process_instance->odometer);
// // 	//PR_MOVE_TO(AR_SYSTEM_BUF_O->s_types.short_value - PR_ODOMETER_I);
// // 	i = CW_ITERATOR;
// // 	while (++i < CW_REG_SIZE)
// // 	{
// // 		BU_DATA_O[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// // 		p_process_instance->cw_move_to(p_process_instance, 1);
// // 	}
// // 	p_process_instance->cw_conversion(p_process_instance, p_buffer_obj, CW_INT, PR_BYTE);
// // 	p_process_instance->cw_carriage_return(p_process_instance, PR_ADDIT_SAVE);
// // }

// // static void	cw_read_operation(t_process *p_process_instance,
// // 				t_arena *p_arena_obj, t_buffer *p_buffer_obj, int input_arg)
// // {
// // 	t_iter	i;

// // 	p_buffer_obj->cw_erase_data(p_buffer_obj);
// // 	if (input_arg == CW_REG_CODE)
// // 	{
// // 		PR_CURRENT_REGISTER_I = AR_FIELD_O[PR_CURRENT_LOCATION_I] - 1;
// // 		i = CW_ITERATOR;
// // 		while (++i < CW_INT)
// // 			BU_DATA_O[i] = PR_REGISTERS_I[i + PR_CURRENT_REGISTER_I * CW_REG_SIZE];
// // 		p_process_instance->cw_conversion(p_process_instance, p_buffer_obj, CW_INT, PR_BYTE);
// // 		p_process_instance->cw_move_to(p_process_instance, CW_REG_CODE_SIZE);
// // 	}
// // 	else if (input_arg == CW_DIR_CODE)
// // 	{
// // 		i = 4 - PR_CURRENT_COMMAND_I->dir_size;
// // 		while (i < CW_REG_SIZE)
// // 		{
// // 			BU_DATA_O[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// // 			++i;
// // 			p_process_instance->cw_move_to(p_process_instance, 1);
// // 		}
// // 		p_process_instance->cw_conversion(p_process_instance, p_buffer_obj, 4 - PR_CURRENT_COMMAND_I->dir_size, PR_BYTE);
// // 	}
// // 	else if (input_arg == CW_IND_CODE)
// // 		cw_ind_read_handle(p_process_instance, p_arena_obj, p_buffer_obj, i);
// // 	else
// // 		cw_error_catcher(PR_OBJECT_NAME, PR_MEMORY_ERROR, __FILE__, __LINE__);
// // }

// void	cw_read_operation(t_process *p_process_instance, t_arena *p_arena_obj, t_buffer *p_buffer_obj, int input_arg)
// {
// 	if (input_arg == CW_REG_CODE)
// 	{
// 		PR_CURRENT_REGISTER_I = AR_FIELD_O[PR_CURRENT_LOCATION_I] - 1;
// 		ft_memset(BU_DATA_O, 0, CW_REG_SIZE);
// 		for (int i = CW_INT; i < CW_REG_SIZE; ++i)
// 			BU_DATA_O[i] = PR_REGISTERS_I[i + PR_CURRENT_REGISTER_I * CW_REG_SIZE];
// 		p_process_instance->cw_conversion(p_process_instance, p_buffer_obj, CW_INT, PR_BYTE);
// 		p_process_instance->cw_move_to(p_process_instance, CW_REG_CODE_SIZE);
// 	}
// 	else if (input_arg == CW_DIR_CODE)
// 	{
// 		ft_memset(BU_DATA_O, 0, CW_REG_SIZE);
// 		for (int i = 4 - p_process_instance->p_current_command->dir_size; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
// 			BU_DATA_O[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// 		p_process_instance->cw_conversion(p_process_instance, p_buffer_obj, 4 - p_process_instance->p_current_command->dir_size, PR_BYTE);
// 	}
// 	else if (input_arg == CW_IND_CODE)
// 	{
// 		ft_memset(AR_BUFFERS_O[CW_SYSTEM_BUF]->p_data, 0, CW_REG_SIZE);
// 		ft_memset(BU_DATA_O, 0, CW_REG_SIZE);
// 		for (int i = CW_SHORT; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
// 			AR_BUFFERS_O[CW_SYSTEM_BUF]->p_data[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// 		p_process_instance->cw_conversion(p_process_instance, AR_BUFFERS_O[CW_SYSTEM_BUF], CW_SHORT, PR_BYTE);
// 		if (p_process_instance->p_current_command->id != CO_LLD)
// 			AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value %= IDX_MOD;
// 			AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value %= MEM_SIZE;
// 		p_process_instance->cw_save_pos(p_process_instance, PR_ADDIT_SAVE);
// 		p_process_instance->cw_move_to(p_process_instance, AR_BUFFERS_O[CW_SYSTEM_BUF]->s_types.short_value - p_process_instance->odometer);
// 		for (int i = CW_INT; i < CW_REG_SIZE; ++i, p_process_instance->cw_move_to(p_process_instance, 1))
// 			BU_DATA_O[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// 		p_process_instance->cw_conversion(p_process_instance, p_buffer_obj, CW_INT, PR_BYTE);
// 		p_process_instance->cw_carriage_return(p_process_instance, PR_ADDIT_SAVE);
// 	}
// 	else
// 		cw_error_catcher(PR_OBJECT_NAME, PR_MEMORY_ERROR, __FILE__, __LINE__);
// }

extern void	cw_process_read_write_functions_linker(t_process *p_process_linker)
{
	p_process_linker->cw_read_operation = cw_read_operation;
	p_process_linker->cw_write_operation = cw_write_operation;
}

// static void	cw_ind_read_handle(t_process *p_process_instance,
// 						t_arena *p_arena_obj, t_buffer *p_buffer_obj, t_iter i)
// {
// 	AR_BUFFERS_O[CW_SYSTEM_BUF]->cw_erase_data(AR_BUFFERS_O[CW_SYSTEM_BUF]);
// 	p_buffer_obj->cw_erase_data(p_buffer_obj);
// 	i = CW_SHORT - 1;
// 	while (++i < CW_REG_SIZE)
// 	{
// 		AR_SYSTEM_BUF_O->p_data[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// 		p_process_instance->cw_move_to(p_process_instance, 1);
// 	}
// 	p_process_instance->cw_conversion(p_process_instance, AR_SYSTEM_BUF_O, CW_SHORT, PR_BYTE);
// 	if (p_process_instance->p_current_command->id != CO_LLD)
// 		AR_SYSTEM_BUF_O->s_types.short_value %= IDX_MOD;
// 	AR_SYSTEM_BUF_O->s_types.short_value %= MEM_SIZE;
// 	p_process_instance->cw_save_pos(p_process_instance, PR_ADDIT_SAVE);
// 	PR_MOVE_TO(AR_SYSTEM_BUF_O->s_types.short_value - PR_ODOMETER_I);
// 	i = CW_ITERATOR;
// 	while (++i < CW_REG_SIZE)
// 	{
// 		BU_DATA_O[i] = AR_FIELD_O[PR_CURRENT_LOCATION_I];
// 		p_process_instance->cw_move_to(p_process_instance, 1);
// 	}
// 	p_process_instance->cw_conversion(p_process_instance, p_buffer_obj, CW_INT, PR_BYTE);
// 	p_process_instance->cw_carriage_return(p_process_instance, PR_ADDIT_SAVE);
// }

// extern void	cw_process_read_write_functions_linker(t_process *p_process_linker)
// {
// 	p_process_linker->cw_read_operation = cw_read_operation;
// 	p_process_linker->cw_write_operation = cw_write_operation;
// }
